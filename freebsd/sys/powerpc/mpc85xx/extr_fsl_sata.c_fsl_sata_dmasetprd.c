#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_8__ {int nsegs; int /*<<< orphan*/  data_map; } ;
struct fsl_sata_slot {int ttl; TYPE_4__* ccb; TYPE_2__ dma; struct fsl_sata_channel* ch; } ;
struct fsl_sata_dma_prd {void* dwc_flg; void* dba; } ;
struct fsl_sata_cmd_tab {struct fsl_sata_dma_prd* prd_tab; } ;
struct TYPE_7__ {int /*<<< orphan*/  data_tag; } ;
struct fsl_sata_channel {TYPE_1__ dma; int /*<<< orphan*/  dev; } ;
struct TYPE_11__ {int ds_len; int /*<<< orphan*/  ds_addr; } ;
typedef  TYPE_5__ bus_dma_segment_t ;
struct TYPE_9__ {int flags; } ;
struct TYPE_10__ {TYPE_3__ ccb_h; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_DMASYNC_PREREAD ; 
 int /*<<< orphan*/  BUS_DMASYNC_PREWRITE ; 
 int CAM_DIR_IN ; 
 struct fsl_sata_cmd_tab* FSL_SATA_CTP (struct fsl_sata_channel*,struct fsl_sata_slot*) ; 
 int FSL_SATA_CTP_BUS (struct fsl_sata_channel*,struct fsl_sata_slot*) ; 
 int /*<<< orphan*/  FSL_SATA_ERR_INVALID ; 
 int FSL_SATA_PRD_EXT ; 
 int FSL_SATA_PRD_EXT_INDEX ; 
 int FSL_SATA_PRD_MAX_DIRECT ; 
 int FSL_SATA_PRD_OFFSET (int) ; 
 int FSL_SATA_PRD_SNOOP ; 
 int FSL_SATA_SG_ENTRIES ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  fsl_sata_end_transaction (struct fsl_sata_slot*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fsl_sata_execute_transaction (struct fsl_sata_slot*) ; 
 void* htole32 (int) ; 
 int roundup2 (int,int) ; 

__attribute__((used)) static void
fsl_sata_dmasetprd(void *arg, bus_dma_segment_t *segs, int nsegs, int error)
{    
	struct fsl_sata_slot *slot = arg;
	struct fsl_sata_channel *ch = slot->ch;
	struct fsl_sata_cmd_tab *ctp;
	struct fsl_sata_dma_prd *prd;
	int i, j, len, extlen;

	if (error) {
		device_printf(ch->dev, "DMA load error %d\n", error);
		fsl_sata_end_transaction(slot, FSL_SATA_ERR_INVALID);
		return;
	}
	KASSERT(nsegs <= FSL_SATA_SG_ENTRIES - 1,
	    ("too many DMA segment entries\n"));
	/* Get a piece of the workspace for this request */
	ctp = FSL_SATA_CTP(ch, slot);
	/* Fill S/G table */
	prd = &ctp->prd_tab[0];
	for (i = 0, j = 0; i < nsegs; i++, j++) {
		if (j == FSL_SATA_PRD_EXT_INDEX &&
		    FSL_SATA_PRD_MAX_DIRECT < nsegs) {
			prd[j].dba = htole32(FSL_SATA_CTP_BUS(ch, slot) +
				     FSL_SATA_PRD_OFFSET(j+1));
			j++;
			extlen = 0;
		}
		len = segs[i].ds_len;
		len = roundup2(len, sizeof(uint32_t));
		prd[j].dba = htole32((uint32_t)segs[i].ds_addr);
		prd[j].dwc_flg = htole32(FSL_SATA_PRD_SNOOP | len);
		slot->ttl += len;
		if (j > FSL_SATA_PRD_MAX_DIRECT)
			extlen += len;
	}
	slot->dma.nsegs = j;
	if (j > FSL_SATA_PRD_MAX_DIRECT)
		prd[FSL_SATA_PRD_EXT_INDEX].dwc_flg = 
		    htole32(FSL_SATA_PRD_SNOOP | FSL_SATA_PRD_EXT | extlen);
	bus_dmamap_sync(ch->dma.data_tag, slot->dma.data_map,
	    ((slot->ccb->ccb_h.flags & CAM_DIR_IN) ?
	    BUS_DMASYNC_PREREAD : BUS_DMASYNC_PREWRITE));
	fsl_sata_execute_transaction(slot);
}