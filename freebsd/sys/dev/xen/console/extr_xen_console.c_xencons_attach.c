#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct xencons_priv {TYPE_1__* ops; int /*<<< orphan*/  callout; } ;
struct tty {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {int (* init ) (int /*<<< orphan*/ ,struct tty*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/ * EVENTHANDLER_REGISTER (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct tty*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SHUTDOWN_PRI_DEFAULT ; 
 int /*<<< orphan*/  callout_init_mtx (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  device_set_softc (int /*<<< orphan*/ ,struct tty*) ; 
 int /*<<< orphan*/  driver_name ; 
 struct xencons_priv main_cons ; 
 int /*<<< orphan*/  shutdown_post_sync ; 
 int stub1 (int /*<<< orphan*/ ,struct tty*,int /*<<< orphan*/ ) ; 
 struct tty* tty_alloc (int /*<<< orphan*/ *,struct xencons_priv*) ; 
 int /*<<< orphan*/  tty_getlock (struct tty*) ; 
 int /*<<< orphan*/  tty_makedev (struct tty*,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xencons_intr ; 
 int /*<<< orphan*/  xencons_shutdown ; 
 int /*<<< orphan*/  xencons_ttydevsw ; 

__attribute__((used)) static int
xencons_attach(device_t dev)
{
	struct tty *tp;
	/*
	 * The main console is already allocated statically in order to
	 * support low-level console
	 */
	struct xencons_priv *cons;
	int err;

	cons = &main_cons;

	tp = tty_alloc(&xencons_ttydevsw, cons);
	tty_makedev(tp, NULL, "%s%r", driver_name, 0);
	device_set_softc(dev, tp);

	callout_init_mtx(&cons->callout, tty_getlock(tp), 0);

	err = cons->ops->init(dev, tp, xencons_intr);
	if (err != 0) {
		device_printf(dev, "Unable to initialize the console (%d)\n",
		    err);
		return (err);
	}

	/* register handler to flush console on shutdown */
	if ((EVENTHANDLER_REGISTER(shutdown_post_sync, xencons_shutdown,
	    tp, SHUTDOWN_PRI_DEFAULT)) == NULL)
		device_printf(dev, "shutdown event registration failed!\n");

	return (0);
}