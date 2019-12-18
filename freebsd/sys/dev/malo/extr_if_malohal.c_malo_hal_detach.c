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
struct malo_hal {int /*<<< orphan*/  mh_mtx; int /*<<< orphan*/  mh_dmat; int /*<<< orphan*/  mh_dmamap; int /*<<< orphan*/  mh_cmdbuf; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  bus_dma_tag_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamem_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct malo_hal*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 

void
malo_hal_detach(struct malo_hal *mh)
{

	bus_dmamem_free(mh->mh_dmat, mh->mh_cmdbuf, mh->mh_dmamap);
	bus_dma_tag_destroy(mh->mh_dmat);
	mtx_destroy(&mh->mh_mtx);
	free(mh, M_DEVBUF);
}