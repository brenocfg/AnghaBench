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
typedef  int uint32_t ;
struct kobject {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int OPAL_SUCCESS ; 
 int /*<<< orphan*/  create_dump_obj (int,int,int) ; 
 int /*<<< orphan*/  dump_kset ; 
 int dump_read_info (int*,int*,int*) ; 
 int /*<<< orphan*/  kobject_put (struct kobject*) ; 
 struct kobject* kset_find_obj (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int,int) ; 

__attribute__((used)) static irqreturn_t process_dump(int irq, void *data)
{
	int rc;
	uint32_t dump_id, dump_size, dump_type;
	char name[22];
	struct kobject *kobj;

	rc = dump_read_info(&dump_id, &dump_size, &dump_type);
	if (rc != OPAL_SUCCESS)
		return IRQ_HANDLED;

	sprintf(name, "0x%x-0x%x", dump_type, dump_id);

	/* we may get notified twice, let's handle
	 * that gracefully and not create two conflicting
	 * entries.
	 */
	kobj = kset_find_obj(dump_kset, name);
	if (kobj) {
		/* Drop reference added by kset_find_obj() */
		kobject_put(kobj);
		return IRQ_HANDLED;
	}

	create_dump_obj(dump_id, dump_size, dump_type);

	return IRQ_HANDLED;
}