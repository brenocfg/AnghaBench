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
struct TYPE_2__ {int /*<<< orphan*/  csts; int /*<<< orphan*/  cc; } ;
struct pci_nvme_softc {scalar_t__ pending_ios; int /*<<< orphan*/  iosemlock; int /*<<< orphan*/  mtx; TYPE_1__ regs; struct pci_nvme_ioreq* ioreqs_free; } ;
struct pci_nvme_ioreq {struct pci_nvme_ioreq* next; scalar_t__ sqid; int /*<<< orphan*/ * nvme_sq; int /*<<< orphan*/ * sc; } ;

/* Variables and functions */
 scalar_t__ NVME_CC_GET_EN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NVME_CSTS_GET_RDY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NVME_CSTS_RDY ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sem_post (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
pci_nvme_release_ioreq(struct pci_nvme_softc *sc, struct pci_nvme_ioreq *req)
{
	req->sc = NULL;
	req->nvme_sq = NULL;
	req->sqid = 0;

	pthread_mutex_lock(&sc->mtx);

	req->next = sc->ioreqs_free;
	sc->ioreqs_free = req;
	sc->pending_ios--;

	/* when no more IO pending, can set to ready if device reset/enabled */
	if (sc->pending_ios == 0 &&
	    NVME_CC_GET_EN(sc->regs.cc) && !(NVME_CSTS_GET_RDY(sc->regs.csts)))
		sc->regs.csts |= NVME_CSTS_RDY;

	pthread_mutex_unlock(&sc->mtx);

	sem_post(&sc->iosemlock);
}