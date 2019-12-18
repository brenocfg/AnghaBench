#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  void* uint64_t ;
struct TYPE_10__ {int /*<<< orphan*/  kset; } ;
struct TYPE_9__ {char* name; int mode; } ;
struct TYPE_11__ {size_t size; int /*<<< orphan*/  read; TYPE_1__ attr; } ;
struct elog_obj {size_t size; TYPE_2__ kobj; TYPE_3__ raw_attr; int /*<<< orphan*/ * buffer; void* id; void* type; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  KOBJ_ADD ; 
 int OPAL_SUCCESS ; 
 int /*<<< orphan*/  __pa (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  elog_kset ; 
 int /*<<< orphan*/  elog_ktype ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int kobject_add (TYPE_2__*,int /*<<< orphan*/ *,char*,void*) ; 
 int /*<<< orphan*/  kobject_init (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kobject_put (TYPE_2__*) ; 
 int /*<<< orphan*/  kobject_uevent (TYPE_2__*,int /*<<< orphan*/ ) ; 
 void* kzalloc (int,int /*<<< orphan*/ ) ; 
 int opal_read_elog (int /*<<< orphan*/ ,int,void*) ; 
 int /*<<< orphan*/  pr_err (char*,void*) ; 
 int /*<<< orphan*/  raw_attr_read ; 
 int /*<<< orphan*/  sysfs_bin_attr_init (TYPE_3__*) ; 
 int sysfs_create_bin_file (TYPE_2__*,TYPE_3__*) ; 

__attribute__((used)) static struct elog_obj *create_elog_obj(uint64_t id, size_t size, uint64_t type)
{
	struct elog_obj *elog;
	int rc;

	elog = kzalloc(sizeof(*elog), GFP_KERNEL);
	if (!elog)
		return NULL;

	elog->kobj.kset = elog_kset;

	kobject_init(&elog->kobj, &elog_ktype);

	sysfs_bin_attr_init(&elog->raw_attr);

	elog->raw_attr.attr.name = "raw";
	elog->raw_attr.attr.mode = 0400;
	elog->raw_attr.size = size;
	elog->raw_attr.read = raw_attr_read;

	elog->id = id;
	elog->size = size;
	elog->type = type;

	elog->buffer = kzalloc(elog->size, GFP_KERNEL);

	if (elog->buffer) {
		rc = opal_read_elog(__pa(elog->buffer),
					 elog->size, elog->id);
		if (rc != OPAL_SUCCESS) {
			pr_err("ELOG: log read failed for log-id=%llx\n",
			       elog->id);
			kfree(elog->buffer);
			elog->buffer = NULL;
		}
	}

	rc = kobject_add(&elog->kobj, NULL, "0x%llx", id);
	if (rc) {
		kobject_put(&elog->kobj);
		return NULL;
	}

	rc = sysfs_create_bin_file(&elog->kobj, &elog->raw_attr);
	if (rc) {
		kobject_put(&elog->kobj);
		return NULL;
	}

	kobject_uevent(&elog->kobj, KOBJ_ADD);

	return elog;
}