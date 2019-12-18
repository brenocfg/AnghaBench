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
struct kobject {int /*<<< orphan*/  parent; } ;
struct dmi_entry_attr_show_data {char* buf; struct attribute* attr; } ;
struct attribute {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  dmi_entry_attr_show_helper ; 
 int /*<<< orphan*/  find_dmi_entry (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct dmi_entry_attr_show_data*) ; 
 int /*<<< orphan*/  to_entry (int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t dmi_entry_attr_show(struct kobject *kobj,
				   struct attribute *attr,
				   char *buf)
{
	struct dmi_entry_attr_show_data data = {
		.attr = attr,
		.buf  = buf,
	};
	/* Find the entry according to our parent and call the
	 * normalized show method hanging off of the attribute */
	return find_dmi_entry(to_entry(kobj->parent),
			      dmi_entry_attr_show_helper, &data);
}