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
typedef  scalar_t__ uint64_t ;
struct kobject {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
typedef  int /*<<< orphan*/  __be64 ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 scalar_t__ OPAL_MAX_ERRLOG_SIZE ; 
 int OPAL_SUCCESS ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 scalar_t__ be64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  create_elog_obj (scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  elog_kset ; 
 int /*<<< orphan*/  kobject_put (struct kobject*) ; 
 struct kobject* kset_find_obj (int /*<<< orphan*/ ,char*) ; 
 int opal_get_elog_size (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,scalar_t__) ; 

__attribute__((used)) static irqreturn_t elog_event(int irq, void *data)
{
	__be64 size;
	__be64 id;
	__be64 type;
	uint64_t elog_size;
	uint64_t log_id;
	uint64_t elog_type;
	int rc;
	char name[2+16+1];
	struct kobject *kobj;

	rc = opal_get_elog_size(&id, &size, &type);
	if (rc != OPAL_SUCCESS) {
		pr_err("ELOG: OPAL log info read failed\n");
		return IRQ_HANDLED;
	}

	elog_size = be64_to_cpu(size);
	log_id = be64_to_cpu(id);
	elog_type = be64_to_cpu(type);

	WARN_ON(elog_size > OPAL_MAX_ERRLOG_SIZE);

	if (elog_size >= OPAL_MAX_ERRLOG_SIZE)
		elog_size  =  OPAL_MAX_ERRLOG_SIZE;

	sprintf(name, "0x%llx", log_id);

	/* we may get notified twice, let's handle
	 * that gracefully and not create two conflicting
	 * entries.
	 */
	kobj = kset_find_obj(elog_kset, name);
	if (kobj) {
		/* Drop reference added by kset_find_obj() */
		kobject_put(kobj);
		return IRQ_HANDLED;
	}

	create_elog_obj(log_id, elog_size, elog_type);

	return IRQ_HANDLED;
}