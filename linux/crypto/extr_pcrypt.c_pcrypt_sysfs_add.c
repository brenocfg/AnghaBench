#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  kset; } ;
struct padata_instance {TYPE_1__ kobj; } ;

/* Variables and functions */
 int /*<<< orphan*/  KOBJ_ADD ; 
 int kobject_add (TYPE_1__*,int /*<<< orphan*/ *,char*,char const*) ; 
 int /*<<< orphan*/  kobject_uevent (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcrypt_kset ; 

__attribute__((used)) static int pcrypt_sysfs_add(struct padata_instance *pinst, const char *name)
{
	int ret;

	pinst->kobj.kset = pcrypt_kset;
	ret = kobject_add(&pinst->kobj, NULL, "%s", name);
	if (!ret)
		kobject_uevent(&pinst->kobj, KOBJ_ADD);

	return ret;
}