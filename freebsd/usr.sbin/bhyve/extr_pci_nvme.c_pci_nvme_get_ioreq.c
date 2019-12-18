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
struct pci_nvme_softc {int /*<<< orphan*/  mtx; int /*<<< orphan*/  pending_ios; struct pci_nvme_ioreq* ioreqs_free; int /*<<< orphan*/  iosemlock; } ;
struct TYPE_2__ {struct pci_nvme_ioreq* br_param; scalar_t__ br_resid; scalar_t__ br_offset; scalar_t__ br_iovcnt; } ;
struct pci_nvme_ioreq {scalar_t__ prev_size; scalar_t__ prev_gpaddr; TYPE_1__ io_req; struct pci_nvme_softc* sc; struct pci_nvme_ioreq* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sem_wait (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct pci_nvme_ioreq *
pci_nvme_get_ioreq(struct pci_nvme_softc *sc)
{
	struct pci_nvme_ioreq *req = NULL;;

	sem_wait(&sc->iosemlock);
	pthread_mutex_lock(&sc->mtx);

	req = sc->ioreqs_free;
	assert(req != NULL);

	sc->ioreqs_free = req->next;

	req->next = NULL;
	req->sc = sc;

	sc->pending_ios++;

	pthread_mutex_unlock(&sc->mtx);

	req->io_req.br_iovcnt = 0;
	req->io_req.br_offset = 0;
	req->io_req.br_resid = 0;
	req->io_req.br_param = req;
	req->prev_gpaddr = 0;
	req->prev_size = 0;

	return req;
}