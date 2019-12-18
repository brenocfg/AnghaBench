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
struct module {int dummy; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  EVENTHANDLER_DEREGISTER (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVENTHANDLER_PRI_ANY ; 
 int /*<<< orphan*/  EVENTHANDLER_REGISTER (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INT_MAX ; 
#define  MOD_LOAD 129 
#define  MOD_UNLOAD 128 
 int /*<<< orphan*/  delete_unrhdr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  new_unrhdr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uhso_etag ; 
 int /*<<< orphan*/  uhso_ifnet_unit ; 
 int /*<<< orphan*/  uhso_test_autoinst ; 
 int /*<<< orphan*/  usb_dev_configured ; 

__attribute__((used)) static int
uhso_driver_loaded(struct module *mod, int what, void *arg)
{
	switch (what) {
	case MOD_LOAD:
		/* register our autoinstall handler */
		uhso_etag = EVENTHANDLER_REGISTER(usb_dev_configured,
		    uhso_test_autoinst, NULL, EVENTHANDLER_PRI_ANY);
		/* create our unit allocator for inet devs */
		uhso_ifnet_unit = new_unrhdr(0, INT_MAX, NULL);
		break;
	case MOD_UNLOAD:
		EVENTHANDLER_DEREGISTER(usb_dev_configured, uhso_etag);
		delete_unrhdr(uhso_ifnet_unit);
		break;
	default:
		return (EOPNOTSUPP);
	}
	return (0);
}