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
struct mpt_softc {scalar_t__ request_dmat; scalar_t__ buffer_dmat; int /*<<< orphan*/  request_dmap; int /*<<< orphan*/  request; TYPE_1__* request_pool; } ;
struct TYPE_2__ {int /*<<< orphan*/  dmap; } ;

/* Variables and functions */
 int MPT_MAX_REQUESTS (struct mpt_softc*) ; 
 int /*<<< orphan*/  MPT_PRT_DEBUG ; 
 int /*<<< orphan*/  bus_dma_tag_destroy (scalar_t__) ; 
 int /*<<< orphan*/  bus_dmamap_destroy (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamap_unload (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamem_free (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpt_lprt (struct mpt_softc*,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
mpt_dma_buf_free(struct mpt_softc *mpt)
{
	int i;

	if (mpt->request_dmat == 0) {
		mpt_lprt(mpt, MPT_PRT_DEBUG, "already released dma memory\n");
		return;
	}
	for (i = 0; i < MPT_MAX_REQUESTS(mpt); i++) {
		bus_dmamap_destroy(mpt->buffer_dmat, mpt->request_pool[i].dmap);
	}
	bus_dmamap_unload(mpt->request_dmat, mpt->request_dmap);
	bus_dmamem_free(mpt->request_dmat, mpt->request, mpt->request_dmap);
	bus_dma_tag_destroy(mpt->request_dmat);
	mpt->request_dmat = 0;
	bus_dma_tag_destroy(mpt->buffer_dmat);
}