#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u_int16_t ;
struct TYPE_6__ {int /*<<< orphan*/  buffer_dmat; int /*<<< orphan*/ * pFreeSRB; int /*<<< orphan*/  sg_dmat; } ;
struct TYPE_5__ {size_t TagNumber; int /*<<< orphan*/  dmamap; int /*<<< orphan*/ * pNextSRB; int /*<<< orphan*/  pSRBSGL; int /*<<< orphan*/  sg_dmamap; } ;
typedef  int /*<<< orphan*/  SGentry ;
typedef  TYPE_1__* PSRB ;
typedef  TYPE_2__* PACB ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_DMA_NOWAIT ; 
 int ENXIO ; 
 int TRM_MAX_SG_LISTENTRY ; 
 size_t TRM_MAX_SRB_CNT ; 
 int bus_dmamap_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_dmamap_load (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ bus_dmamem_alloc (int /*<<< orphan*/ ,void**,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trm_srbmapSG ; 

__attribute__((used)) static int
trm_initSRB(PACB pACB)
{
    	u_int16_t    i;
	PSRB    pSRB;
	int error;

	for (i = 0; i < TRM_MAX_SRB_CNT; i++) {
	       	pSRB = (PSRB)&pACB->pFreeSRB[i];

		if (bus_dmamem_alloc(pACB->sg_dmat, (void **)&pSRB->pSRBSGL,
		    BUS_DMA_NOWAIT, &pSRB->sg_dmamap) !=0 ) {
			return ENXIO;
		}
		bus_dmamap_load(pACB->sg_dmat, pSRB->sg_dmamap, pSRB->pSRBSGL,
		    TRM_MAX_SG_LISTENTRY * sizeof(SGentry),
		    trm_srbmapSG, pSRB, /*flags*/0);
		if (i != TRM_MAX_SRB_CNT - 1) {
			/*
			 * link all SRB 
			 */
			pSRB->pNextSRB = &pACB->pFreeSRB[i+1];
		} else {
			/*
			 * load NULL to NextSRB of the last SRB
			 */
			pSRB->pNextSRB = NULL;
		}
		pSRB->TagNumber = i;

		/*
		 * Create the dmamap.  This is no longer optional!
		 */
		if ((error = bus_dmamap_create(pACB->buffer_dmat, 0,
					       &pSRB->dmamap)) != 0)
			return (error);

	}
	return (0);
}