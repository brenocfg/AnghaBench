#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  kset; } ;
struct TYPE_4__ {void* esre1; } ;
struct esre_entry {int /*<<< orphan*/  list; TYPE_2__ kobj; TYPE_1__ esre; } ;
struct TYPE_6__ {int fw_resource_version; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  entry_list ; 
 int /*<<< orphan*/  esre1_ktype ; 
 TYPE_3__* esrt ; 
 int /*<<< orphan*/  esrt_kset ; 
 int /*<<< orphan*/  kfree (struct esre_entry*) ; 
 int kobject_init_and_add (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int) ; 
 struct esre_entry* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int esre_create_sysfs_entry(void *esre, int entry_num)
{
	struct esre_entry *entry;

	entry = kzalloc(sizeof(*entry), GFP_KERNEL);
	if (!entry)
		return -ENOMEM;

	entry->kobj.kset = esrt_kset;

	if (esrt->fw_resource_version == 1) {
		int rc = 0;

		entry->esre.esre1 = esre;
		rc = kobject_init_and_add(&entry->kobj, &esre1_ktype, NULL,
					  "entry%d", entry_num);
		if (rc) {
			kfree(entry);
			return rc;
		}
	}

	list_add_tail(&entry->list, &entry_list);
	return 0;
}