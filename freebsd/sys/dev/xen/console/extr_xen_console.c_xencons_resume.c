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
struct xencons_priv {TYPE_1__* ops; int /*<<< orphan*/  intr_handle; } ;
struct tty {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {int (* init ) (int /*<<< orphan*/ ,struct tty*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 struct tty* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int) ; 
 int stub1 (int /*<<< orphan*/ ,struct tty*,int /*<<< orphan*/ ) ; 
 struct xencons_priv* tty_softc (struct tty*) ; 
 int /*<<< orphan*/  xen_intr_unbind (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xencons_intr ; 

__attribute__((used)) static int
xencons_resume(device_t dev)
{
	struct xencons_priv *cons;
	struct tty *tp;
	int err;

	tp = device_get_softc(dev);
	cons = tty_softc(tp);
	xen_intr_unbind(&cons->intr_handle);

	err = cons->ops->init(dev, tp, xencons_intr);
	if (err != 0) {
		device_printf(dev, "Unable to resume the console (%d)\n", err);
		return (err);
	}

	return (0);
}