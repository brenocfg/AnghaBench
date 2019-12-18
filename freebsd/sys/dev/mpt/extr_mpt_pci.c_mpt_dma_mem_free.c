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
struct mpt_softc {int /*<<< orphan*/ * request_pool; int /*<<< orphan*/ * reply_dmat; int /*<<< orphan*/ * parent_dmat; int /*<<< orphan*/  reply_dmap; int /*<<< orphan*/  reply; } ;

/* Variables and functions */
 int /*<<< orphan*/  MPT_PRT_DEBUG ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  bus_dma_tag_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_dmamap_unload (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamem_free (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpt_lprt (struct mpt_softc*,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
mpt_dma_mem_free(struct mpt_softc *mpt)
{

        /* Make sure we aren't double destroying */
        if (mpt->reply_dmat == 0) {
		mpt_lprt(mpt, MPT_PRT_DEBUG, "already released dma memory\n");
		return;
        }
                
	bus_dmamap_unload(mpt->reply_dmat, mpt->reply_dmap);
	bus_dmamem_free(mpt->reply_dmat, mpt->reply, mpt->reply_dmap);
	bus_dma_tag_destroy(mpt->reply_dmat);
	bus_dma_tag_destroy(mpt->parent_dmat);
	mpt->reply_dmat = NULL;
	free(mpt->request_pool, M_DEVBUF);
	mpt->request_pool = NULL;
}