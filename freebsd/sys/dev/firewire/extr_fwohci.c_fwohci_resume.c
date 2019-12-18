#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int nisodma; int /*<<< orphan*/  (* ibr ) (TYPE_2__*) ;int /*<<< orphan*/  (* irx_enable ) (TYPE_2__*,int) ;int /*<<< orphan*/  dev; } ;
struct fwohci_softc {TYPE_2__ fc; TYPE_1__* ir; } ;
struct fw_xferq {int flag; int /*<<< orphan*/  stfree; int /*<<< orphan*/  stdma; } ;
struct fw_bulkxfer {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_4__ {struct fw_xferq xferq; } ;

/* Variables and functions */
 int FWXFERQ_RUNNING ; 
 struct fw_bulkxfer* STAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct fw_bulkxfer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STAILQ_REMOVE_HEAD (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_generic_resume (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  fwohci_reset (struct fwohci_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  link ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,int) ; 
 int /*<<< orphan*/  stub2 (TYPE_2__*) ; 

int
fwohci_resume(struct fwohci_softc *sc, device_t dev)
{
	int i;
	struct fw_xferq *ir;
	struct fw_bulkxfer *chunk;

	fwohci_reset(sc, dev);
	/* XXX resume isochronous receive automatically. (how about TX?) */
	for (i = 0; i < sc->fc.nisodma; i++) {
		ir = &sc->ir[i].xferq;
		if ((ir->flag & FWXFERQ_RUNNING) != 0) {
			device_printf(sc->fc.dev,
				"resume iso receive ch: %d\n", i);
			ir->flag &= ~FWXFERQ_RUNNING;
			/* requeue stdma to stfree */
			while ((chunk = STAILQ_FIRST(&ir->stdma)) != NULL) {
				STAILQ_REMOVE_HEAD(&ir->stdma, link);
				STAILQ_INSERT_TAIL(&ir->stfree, chunk, link);
			}
			sc->fc.irx_enable(&sc->fc, i);
		}
	}

	bus_generic_resume(dev);
	sc->fc.ibr(&sc->fc);
	return 0;
}