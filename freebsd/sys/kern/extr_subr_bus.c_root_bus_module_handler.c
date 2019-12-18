#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  module_t ;
typedef  int /*<<< orphan*/  kobj_t ;
typedef  int /*<<< orphan*/  kobj_class_t ;
struct TYPE_4__ {char* desc; int /*<<< orphan*/  state; int /*<<< orphan*/ * driver; } ;

/* Variables and functions */
 int /*<<< orphan*/  DS_ATTACHED ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  FALSE ; 
#define  MOD_LOAD 129 
#define  MOD_SHUTDOWN 128 
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_data_devices ; 
 int /*<<< orphan*/  devclass_find_internal (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_shutdown (TYPE_1__*) ; 
 int /*<<< orphan*/  devinit () ; 
 int /*<<< orphan*/  kobj_class_compile (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kobj_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* make_device (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 TYPE_1__* root_bus ; 
 int /*<<< orphan*/  root_devclass ; 
 int /*<<< orphan*/  root_driver ; 

__attribute__((used)) static int
root_bus_module_handler(module_t mod, int what, void* arg)
{
	switch (what) {
	case MOD_LOAD:
		TAILQ_INIT(&bus_data_devices);
		kobj_class_compile((kobj_class_t) &root_driver);
		root_bus = make_device(NULL, "root", 0);
		root_bus->desc = "System root bus";
		kobj_init((kobj_t) root_bus, (kobj_class_t) &root_driver);
		root_bus->driver = &root_driver;
		root_bus->state = DS_ATTACHED;
		root_devclass = devclass_find_internal("root", NULL, FALSE);
		devinit();
		return (0);

	case MOD_SHUTDOWN:
		device_shutdown(root_bus);
		return (0);
	default:
		return (EOPNOTSUPP);
	}

	return (0);
}