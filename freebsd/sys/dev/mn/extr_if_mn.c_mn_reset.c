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
typedef  int u_int32_t ;
struct TYPE_4__ {int csa; int ccb; int* ts; } ;
struct mn_softc {int tiqb; int riqb; int ltiqb; int lriqb; int piqb; int unit; TYPE_2__ m32_mem; TYPE_1__* m32x; } ;
struct TYPE_3__ {int tiql; int riql; int ltiql; int lriql; int piql; int stat; int cmd; void* piqba; void* lriqba; void* ltiqba; void* riqba; void* tiqba; void* ccba; } ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int NIQB ; 
 int /*<<< orphan*/  bzero (int,int) ; 
 int /*<<< orphan*/  f54_init (struct mn_softc*) ; 
 int /*<<< orphan*/  m32_init (struct mn_softc*) ; 
 int /*<<< orphan*/  printf (char*,int,int) ; 
 void* vtophys (int*) ; 

__attribute__((used)) static int
mn_reset(struct mn_softc *sc)
{
	u_int32_t u;
	int i;

	sc->m32x->ccba = vtophys(&sc->m32_mem.csa);
	sc->m32_mem.csa = vtophys(&sc->m32_mem.ccb);

	bzero(sc->tiqb, sizeof sc->tiqb);
	sc->m32x->tiqba = vtophys(&sc->tiqb);
	sc->m32x->tiql = NIQB / 16 - 1;

	bzero(sc->riqb, sizeof sc->riqb);
	sc->m32x->riqba = vtophys(&sc->riqb);
	sc->m32x->riql = NIQB / 16 - 1;

	bzero(sc->ltiqb, sizeof sc->ltiqb);
	sc->m32x->ltiqba = vtophys(&sc->ltiqb);
	sc->m32x->ltiql = NIQB / 16 - 1;

	bzero(sc->lriqb, sizeof sc->lriqb);
	sc->m32x->lriqba = vtophys(&sc->lriqb);
	sc->m32x->lriql = NIQB / 16 - 1;

	bzero(sc->piqb, sizeof sc->piqb);
	sc->m32x->piqba = vtophys(&sc->piqb);
	sc->m32x->piql = NIQB / 16 - 1;

	m32_init(sc);
	f54_init(sc);

	u = sc->m32x->stat; 
	sc->m32x->stat = u;
	sc->m32_mem.ccb = 0x4;
	sc->m32x->cmd = 0x1;
	DELAY(1000);
	u = sc->m32x->stat;
	sc->m32x->stat = u;

	/* set all timeslots to known state */
	for (i = 0; i < 32; i++)
		sc->m32_mem.ts[i] = 0x20002000;

	if (!(u & 1)) {
		printf(
"mn%d: WARNING: Controller failed the PCI bus-master test.\n"
"mn%d: WARNING: Use a PCI slot which can support bus-master cards.\n",
		    sc->unit, sc->unit);
		return  (0);
	}
	return (1);
}