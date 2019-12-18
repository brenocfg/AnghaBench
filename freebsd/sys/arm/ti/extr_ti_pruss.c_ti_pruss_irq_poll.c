#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ cnt; } ;
struct TYPE_4__ {TYPE_1__ ctl; } ;
struct ti_pruss_irqsc {int /*<<< orphan*/  sc_selinfo; TYPE_2__ tstamps; } ;
struct thread {int dummy; } ;
struct ctl {scalar_t__ cnt; } ;
struct cdev {struct ti_pruss_irqsc* si_drv1; } ;

/* Variables and functions */
 int POLLIN ; 
 int POLLRDNORM ; 
 int /*<<< orphan*/  devfs_get_cdevpriv (void**) ; 
 int /*<<< orphan*/  selrecord (struct thread*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
ti_pruss_irq_poll(struct cdev *dev, int events, struct thread *td)
{
	struct ctl* irqs;
	struct ti_pruss_irqsc *sc;
	sc = dev->si_drv1;

	devfs_get_cdevpriv((void**)&irqs);

	if (events & (POLLIN | POLLRDNORM)) {
		if (sc->tstamps.ctl.cnt != irqs->cnt)
			return events & (POLLIN | POLLRDNORM);
		else
			selrecord(td, &sc->sc_selinfo);
	}
	return 0;
}