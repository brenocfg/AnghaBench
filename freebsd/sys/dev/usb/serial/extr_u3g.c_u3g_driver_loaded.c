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
#define  MOD_LOAD 129 
#define  MOD_UNLOAD 128 
 int /*<<< orphan*/  u3g_etag ; 
 int /*<<< orphan*/  u3g_test_autoinst ; 
 int /*<<< orphan*/  usb_dev_configured ; 

__attribute__((used)) static int
u3g_driver_loaded(struct module *mod, int what, void *arg)
{
	switch (what) {
	case MOD_LOAD:
		/* register our autoinstall handler */
		u3g_etag = EVENTHANDLER_REGISTER(usb_dev_configured,
		    u3g_test_autoinst, NULL, EVENTHANDLER_PRI_ANY);
		break;
	case MOD_UNLOAD:
		EVENTHANDLER_DEREGISTER(usb_dev_configured, u3g_etag);
		break;
	default:
		return (EOPNOTSUPP);
	}
 	return (0);
}