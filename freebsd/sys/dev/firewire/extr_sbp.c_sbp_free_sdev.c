#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  fc; } ;
struct sbp_softc {TYPE_2__ fd; int /*<<< orphan*/  dmat; } ;
struct sbp_dev {int /*<<< orphan*/  dma; TYPE_1__* ocb; int /*<<< orphan*/  login_callout; TYPE_3__* target; } ;
struct TYPE_6__ {struct sbp_softc* sbp; } ;
struct TYPE_4__ {int /*<<< orphan*/  dmamap; int /*<<< orphan*/  timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_SBP ; 
 int /*<<< orphan*/  SBP_LOCK (struct sbp_softc*) ; 
 int SBP_QUEUE_LEN ; 
 int /*<<< orphan*/  SBP_UNLOCK (struct sbp_softc*) ; 
 int /*<<< orphan*/  bus_dmamap_destroy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  callout_drain (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (struct sbp_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fwdma_free (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
sbp_free_sdev(struct sbp_dev *sdev)
{
	struct sbp_softc *sbp;
	int i;

	if (sdev == NULL)
		return;
	sbp = sdev->target->sbp;
	SBP_UNLOCK(sbp);
	callout_drain(&sdev->login_callout);
	for (i = 0; i < SBP_QUEUE_LEN; i++) {
		callout_drain(&sdev->ocb[i].timer);
		bus_dmamap_destroy(sbp->dmat, sdev->ocb[i].dmamap);
	}
	fwdma_free(sbp->fd.fc, &sdev->dma);
	free(sdev, M_SBP);
	SBP_LOCK(sbp);
}