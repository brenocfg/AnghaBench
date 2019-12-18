#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct kobject {int dummy; } ;
struct file {int dummy; } ;
struct elog_obj {int /*<<< orphan*/ * buffer; int /*<<< orphan*/  id; int /*<<< orphan*/  size; } ;
struct bin_attribute {int dummy; } ;
typedef  size_t ssize_t ;
typedef  int loff_t ;

/* Variables and functions */
 size_t EIO ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int OPAL_SUCCESS ; 
 int /*<<< orphan*/  __pa (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kzalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ *,size_t) ; 
 int opal_read_elog (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ) ; 
 struct elog_obj* to_elog_obj (struct kobject*) ; 

__attribute__((used)) static ssize_t raw_attr_read(struct file *filep, struct kobject *kobj,
			     struct bin_attribute *bin_attr,
			     char *buffer, loff_t pos, size_t count)
{
	int opal_rc;

	struct elog_obj *elog = to_elog_obj(kobj);

	/* We may have had an error reading before, so let's retry */
	if (!elog->buffer) {
		elog->buffer = kzalloc(elog->size, GFP_KERNEL);
		if (!elog->buffer)
			return -EIO;

		opal_rc = opal_read_elog(__pa(elog->buffer),
					 elog->size, elog->id);
		if (opal_rc != OPAL_SUCCESS) {
			pr_err("ELOG: log read failed for log-id=%llx\n",
			       elog->id);
			kfree(elog->buffer);
			elog->buffer = NULL;
			return -EIO;
		}
	}

	memcpy(buffer, elog->buffer + pos, count);

	return count;
}