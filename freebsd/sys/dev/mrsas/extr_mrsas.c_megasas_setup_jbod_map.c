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
typedef  int uint32_t ;
struct mrsas_softc {int use_seqnum_jbod_fp; int /*<<< orphan*/  mrsas_dev; scalar_t__* jbodmap_mem; int /*<<< orphan*/ * jbodmap_phys_addr; int /*<<< orphan*/ * jbodmap_dmamap; int /*<<< orphan*/ * jbodmap_tag; int /*<<< orphan*/  mrsas_parent_tag; TYPE_2__* ctrl_info; } ;
struct MR_PD_CFG_SEQ_NUM_SYNC {int dummy; } ;
struct MR_PD_CFG_SEQ {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  useSeqNumJbodFP; } ;
struct TYPE_4__ {TYPE_1__ adapterOperations3; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_DMA_ALLOCNOW ; 
 int /*<<< orphan*/  BUS_DMA_NOWAIT ; 
 int /*<<< orphan*/  BUS_SPACE_MAXADDR ; 
 int /*<<< orphan*/  BUS_SPACE_MAXADDR_32BIT ; 
 int MAX_PHYSICAL_DEVICES ; 
 scalar_t__ bus_dma_tag_create (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ bus_dmamap_load (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ bus_dmamem_alloc (int /*<<< orphan*/ ,void**,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bzero (scalar_t__,int) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  megasas_sync_pd_seq_num (struct mrsas_softc*,int) ; 
 int /*<<< orphan*/  mrsas_addr_cb ; 

void
megasas_setup_jbod_map(struct mrsas_softc *sc)
{
	int i;
	uint32_t pd_seq_map_sz;

	pd_seq_map_sz = sizeof(struct MR_PD_CFG_SEQ_NUM_SYNC) +
	    (sizeof(struct MR_PD_CFG_SEQ) * (MAX_PHYSICAL_DEVICES - 1));

	if (!sc->ctrl_info->adapterOperations3.useSeqNumJbodFP) {
		sc->use_seqnum_jbod_fp = 0;
		return;
	}
	if (sc->jbodmap_mem[0])
		goto skip_alloc;

	for (i = 0; i < 2; i++) {
		if (bus_dma_tag_create(sc->mrsas_parent_tag,
		    4, 0,
		    BUS_SPACE_MAXADDR_32BIT,
		    BUS_SPACE_MAXADDR,
		    NULL, NULL,
		    pd_seq_map_sz,
		    1,
		    pd_seq_map_sz,
		    BUS_DMA_ALLOCNOW,
		    NULL, NULL,
		    &sc->jbodmap_tag[i])) {
			device_printf(sc->mrsas_dev,
			    "Cannot allocate jbod map tag.\n");
			return;
		}
		if (bus_dmamem_alloc(sc->jbodmap_tag[i],
		    (void **)&sc->jbodmap_mem[i],
		    BUS_DMA_NOWAIT, &sc->jbodmap_dmamap[i])) {
			device_printf(sc->mrsas_dev,
			    "Cannot allocate jbod map memory.\n");
			return;
		}
		bzero(sc->jbodmap_mem[i], pd_seq_map_sz);

		if (bus_dmamap_load(sc->jbodmap_tag[i], sc->jbodmap_dmamap[i],
		    sc->jbodmap_mem[i], pd_seq_map_sz,
		    mrsas_addr_cb, &sc->jbodmap_phys_addr[i],
		    BUS_DMA_NOWAIT)) {
			device_printf(sc->mrsas_dev, "Cannot load jbod map memory.\n");
			return;
		}
		if (!sc->jbodmap_mem[i]) {
			device_printf(sc->mrsas_dev,
			    "Cannot allocate memory for jbod map.\n");
			sc->use_seqnum_jbod_fp = 0;
			return;
		}
	}

skip_alloc:
	if (!megasas_sync_pd_seq_num(sc, false) &&
	    !megasas_sync_pd_seq_num(sc, true))
		sc->use_seqnum_jbod_fp = 1;
	else
		sc->use_seqnum_jbod_fp = 0;

	device_printf(sc->mrsas_dev, "Jbod map is supported\n");
}