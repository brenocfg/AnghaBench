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
struct pci_vtscsi_worker {scalar_t__ vsw_exiting; struct pci_vtscsi_queue* vsw_queue; } ;
struct pci_vtscsi_request {int /*<<< orphan*/  vsr_idx; int /*<<< orphan*/  vsr_niov_out; int /*<<< orphan*/  vsr_iov_out; int /*<<< orphan*/  vsr_niov_in; int /*<<< orphan*/  vsr_iov_in; } ;
struct pci_vtscsi_queue {int /*<<< orphan*/  vsq_mtx; int /*<<< orphan*/  vsq_qmtx; int /*<<< orphan*/  vsq_vq; int /*<<< orphan*/  vsq_requests; int /*<<< orphan*/  vsq_cv; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*) ; 
 scalar_t__ STAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 struct pci_vtscsi_request* STAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STAILQ_REMOVE_HEAD (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct pci_vtscsi_request*) ; 
 int pci_vtscsi_request_handle (struct pci_vtscsi_queue*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_cond_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vq_endchains (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vq_relchain (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vsr_link ; 

__attribute__((used)) static void *
pci_vtscsi_proc(void *arg)
{
	struct pci_vtscsi_worker *worker = (struct pci_vtscsi_worker *)arg;
	struct pci_vtscsi_queue *q = worker->vsw_queue;
	struct pci_vtscsi_request *req;
	int iolen;

	for (;;) {
		pthread_mutex_lock(&q->vsq_mtx);

		while (STAILQ_EMPTY(&q->vsq_requests)
		    && !worker->vsw_exiting)
			pthread_cond_wait(&q->vsq_cv, &q->vsq_mtx);

		if (worker->vsw_exiting)
			break;

		req = STAILQ_FIRST(&q->vsq_requests);
		STAILQ_REMOVE_HEAD(&q->vsq_requests, vsr_link);

		pthread_mutex_unlock(&q->vsq_mtx);
		iolen = pci_vtscsi_request_handle(q, req->vsr_iov_in,
		    req->vsr_niov_in, req->vsr_iov_out, req->vsr_niov_out);

		pthread_mutex_lock(&q->vsq_qmtx);
		vq_relchain(q->vsq_vq, req->vsr_idx, iolen);
		vq_endchains(q->vsq_vq, 0);
		pthread_mutex_unlock(&q->vsq_qmtx);

		DPRINTF(("virtio-scsi: request <idx=%d> completed\n",
		    req->vsr_idx));
		free(req);
	}

	pthread_mutex_unlock(&q->vsq_mtx);
	return (NULL);
}