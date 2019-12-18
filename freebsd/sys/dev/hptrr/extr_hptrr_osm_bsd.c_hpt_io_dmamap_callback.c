#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int /*<<< orphan*/  ds_len; int /*<<< orphan*/  ds_addr; } ;
typedef  TYPE_4__ bus_dma_segment_t ;
struct TYPE_12__ {int physical_sg; scalar_t__ data_out; scalar_t__ data_in; } ;
struct TYPE_17__ {TYPE_2__ flags; TYPE_5__* psg; int /*<<< orphan*/  priv; } ;
struct TYPE_16__ {int /*<<< orphan*/  timeout; int /*<<< orphan*/  dma_map; TYPE_3__* vbus_ext; } ;
struct TYPE_11__ {int /*<<< orphan*/  bus; } ;
struct TYPE_15__ {int eot; int /*<<< orphan*/  size; TYPE_1__ addr; } ;
struct TYPE_13__ {int /*<<< orphan*/  io_dmat; } ;
typedef  TYPE_5__* PSG ;
typedef  TYPE_6__* POS_CMDEXT ;
typedef  TYPE_7__* PCOMMAND ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_DMASYNC_PREREAD ; 
 int /*<<< orphan*/  BUS_DMASYNC_PREWRITE ; 
 int /*<<< orphan*/  HPT_ASSERT (int) ; 
 int /*<<< orphan*/  HPT_OSM_TIMEOUT ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_7__*) ; 
 int /*<<< orphan*/  hpt_timeout ; 
 int /*<<< orphan*/  ldm_queue_cmd (TYPE_7__*) ; 
 int os_max_sg_descriptors ; 
 int /*<<< orphan*/  panic (char*) ; 

__attribute__((used)) static void hpt_io_dmamap_callback(void *arg, bus_dma_segment_t *segs, int nsegs, int error)
{
	PCOMMAND pCmd = (PCOMMAND)arg;
	POS_CMDEXT ext = (POS_CMDEXT)pCmd->priv;
	PSG psg = pCmd->psg;
	int idx;
	
	HPT_ASSERT(pCmd->flags.physical_sg);
	
	if (error)
		panic("busdma error");
		
	HPT_ASSERT(nsegs<=os_max_sg_descriptors);

	if (nsegs != 0) {
		for (idx = 0; idx < nsegs; idx++, psg++) {
			psg->addr.bus = segs[idx].ds_addr;
			psg->size = segs[idx].ds_len;
			psg->eot = 0;
		}
			psg[-1].eot = 1;
		
		if (pCmd->flags.data_in) {
			bus_dmamap_sync(ext->vbus_ext->io_dmat, ext->dma_map,
			    BUS_DMASYNC_PREREAD);
		}
		else if (pCmd->flags.data_out) {
			bus_dmamap_sync(ext->vbus_ext->io_dmat, ext->dma_map,
			    BUS_DMASYNC_PREWRITE);
		}
	}
	callout_reset(&ext->timeout, HPT_OSM_TIMEOUT, hpt_timeout, pCmd);
	ldm_queue_cmd(pCmd);
}