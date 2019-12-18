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
struct TYPE_4__ {int /*<<< orphan*/  idx; int /*<<< orphan*/  cnt; } ;
struct TYPE_3__ {TYPE_2__ ctl; } ;
struct ti_pruss_irqsc {TYPE_1__ tstamps; } ;
struct thread {int dummy; } ;
struct ctl {int /*<<< orphan*/  idx; int /*<<< orphan*/  cnt; } ;
struct cdev {struct ti_pruss_irqsc* si_drv1; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int devfs_set_cdevpriv (struct ctl*,int /*<<< orphan*/ ) ; 
 struct ctl* malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ti_pruss_privdtor ; 

__attribute__((used)) static int
ti_pruss_irq_open(struct cdev *dev, int oflags, int devtype, struct thread *td)
{
	struct ctl* irqs;
	struct ti_pruss_irqsc *sc;
	sc = dev->si_drv1;

	irqs = malloc(sizeof(struct ctl), M_DEVBUF, M_WAITOK);
	if (!irqs)
	    return (ENOMEM);

	irqs->cnt = sc->tstamps.ctl.cnt;
	irqs->idx = sc->tstamps.ctl.idx;

	return devfs_set_cdevpriv(irqs, ti_pruss_privdtor);
}