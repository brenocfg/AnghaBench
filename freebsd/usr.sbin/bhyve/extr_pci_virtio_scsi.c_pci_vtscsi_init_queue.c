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
typedef  int /*<<< orphan*/  tname ;
struct pci_vtscsi_worker {int /*<<< orphan*/  vsw_thread; struct pci_vtscsi_queue* vsw_queue; } ;
struct pci_vtscsi_softc {int /*<<< orphan*/ * vss_vq; } ;
struct pci_vtscsi_queue {int /*<<< orphan*/  vsq_workers; int /*<<< orphan*/  vsq_requests; int /*<<< orphan*/  vsq_cv; int /*<<< orphan*/  vsq_qmtx; int /*<<< orphan*/  vsq_mtx; int /*<<< orphan*/ * vsq_vq; struct pci_vtscsi_softc* vsq_sc; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LIST_INSERT_HEAD (int /*<<< orphan*/ *,struct pci_vtscsi_worker*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAXCOMLEN ; 
 int /*<<< orphan*/  STAILQ_INIT (int /*<<< orphan*/ *) ; 
 int VTSCSI_THR_PER_Q ; 
 struct pci_vtscsi_worker* calloc (int,int) ; 
 int /*<<< orphan*/  pci_vtscsi_proc ; 
 int /*<<< orphan*/  pthread_cond_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  pthread_mutex_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_set_name_np (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int,int) ; 
 int /*<<< orphan*/  vsw_link ; 

__attribute__((used)) static int
pci_vtscsi_init_queue(struct pci_vtscsi_softc *sc, 
    struct pci_vtscsi_queue *queue, int num)
{
	struct pci_vtscsi_worker *worker;
	char tname[MAXCOMLEN + 1];
	int i;

	queue->vsq_sc = sc;
	queue->vsq_vq = &sc->vss_vq[num + 2];

	pthread_mutex_init(&queue->vsq_mtx, NULL);
	pthread_mutex_init(&queue->vsq_qmtx, NULL);
	pthread_cond_init(&queue->vsq_cv, NULL);
	STAILQ_INIT(&queue->vsq_requests);
	LIST_INIT(&queue->vsq_workers);

	for (i = 0; i < VTSCSI_THR_PER_Q; i++) {
		worker = calloc(1, sizeof(struct pci_vtscsi_worker));
		worker->vsw_queue = queue;

		pthread_create(&worker->vsw_thread, NULL, &pci_vtscsi_proc,
		    (void *)worker);

		snprintf(tname, sizeof(tname), "vtscsi:%d-%d", num, i);
		pthread_set_name_np(worker->vsw_thread, tname);
		LIST_INSERT_HEAD(&queue->vsq_workers, worker, vsw_link);
	}

	return (0);
}