#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct sysctl_oid {int dummy; } ;
struct TYPE_9__ {char* name; } ;
struct TYPE_8__ {void* oidp; } ;
struct TYPE_7__ {int /*<<< orphan*/  bsddev; TYPE_2__ kobj; } ;

/* Variables and functions */
 int CPUID_CLFSH ; 
 int CTLFLAG_MPSAFE ; 
 int CTLFLAG_RD ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LIST_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  OID_AUTO ; 
 void* SYSCTL_ADD_NODE (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ *,char*) ; 
 struct sysctl_oid* SYSCTL_ADD_ROOT_NODE (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  SYSCTL_CHILDREN (struct sysctl_oid*) ; 
 int VMMAP_HASH_SIZE ; 
 int /*<<< orphan*/  class_register (TYPE_3__*) ; 
 int cpu_feature ; 
 int /*<<< orphan*/  kobject_init (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kobject_set_name (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  linux_class_ktype ; 
 TYPE_3__ linux_class_misc ; 
 TYPE_2__ linux_class_root ; 
 int linux_cpu_has_clflush ; 
 int /*<<< orphan*/  linux_dev_ktype ; 
 TYPE_1__ linux_root_device ; 
 int /*<<< orphan*/  linux_vma_lock ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_devices ; 
 int /*<<< orphan*/  pci_drivers ; 
 int /*<<< orphan*/  pci_lock ; 
 int /*<<< orphan*/  root_bus ; 
 int /*<<< orphan*/  rw_init (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * vmmaphead ; 
 int /*<<< orphan*/  vmmaplock ; 

__attribute__((used)) static void
linux_compat_init(void *arg)
{
	struct sysctl_oid *rootoid;
	int i;

#if defined(__i386__) || defined(__amd64__)
	linux_cpu_has_clflush = (cpu_feature & CPUID_CLFSH);
#endif
	rw_init(&linux_vma_lock, "lkpi-vma-lock");

	rootoid = SYSCTL_ADD_ROOT_NODE(NULL,
	    OID_AUTO, "sys", CTLFLAG_RD|CTLFLAG_MPSAFE, NULL, "sys");
	kobject_init(&linux_class_root, &linux_class_ktype);
	kobject_set_name(&linux_class_root, "class");
	linux_class_root.oidp = SYSCTL_ADD_NODE(NULL, SYSCTL_CHILDREN(rootoid),
	    OID_AUTO, "class", CTLFLAG_RD|CTLFLAG_MPSAFE, NULL, "class");
	kobject_init(&linux_root_device.kobj, &linux_dev_ktype);
	kobject_set_name(&linux_root_device.kobj, "device");
	linux_root_device.kobj.oidp = SYSCTL_ADD_NODE(NULL,
	    SYSCTL_CHILDREN(rootoid), OID_AUTO, "device", CTLFLAG_RD, NULL,
	    "device");
	linux_root_device.bsddev = root_bus;
	linux_class_misc.name = "misc";
	class_register(&linux_class_misc);
	INIT_LIST_HEAD(&pci_drivers);
	INIT_LIST_HEAD(&pci_devices);
	spin_lock_init(&pci_lock);
	mtx_init(&vmmaplock, "IO Map lock", NULL, MTX_DEF);
	for (i = 0; i < VMMAP_HASH_SIZE; i++)
		LIST_INIT(&vmmaphead[i]);
}