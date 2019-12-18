#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int flags; int /*<<< orphan*/  target_lun; int /*<<< orphan*/  target_id; } ;
struct ccb_scsiio {scalar_t__ dxfer_len; scalar_t__ cdb_len; } ;
union ccb {TYPE_1__ ccb_h; struct ccb_scsiio csio; } ;
typedef  void* u_int8_t ;
typedef  scalar_t__ u_int64_t ;
typedef  scalar_t__ u_int32_t ;
struct SG64ENTRY {scalar_t__ length; scalar_t__ address; scalar_t__ addresshigh; } ;
struct SG32ENTRY {scalar_t__ length; scalar_t__ address; } ;
struct ARCMSR_CDB {int Function; scalar_t__ msgPages; scalar_t__ DataLength; int /*<<< orphan*/  Flags; void* sgcount; int /*<<< orphan*/  Cdb; void* CdbLength; int /*<<< orphan*/  LUN; int /*<<< orphan*/  TargetID; scalar_t__ Bus; int /*<<< orphan*/  u; } ;
struct CommandControlBlock {scalar_t__ arc_cdb_size; int /*<<< orphan*/  dm_segs_dmamap; int /*<<< orphan*/  srb_flags; struct AdapterControlBlock* acb; union ccb* pccb; struct ARCMSR_CDB arcmsr_cdb; } ;
struct AdapterControlBlock {int /*<<< orphan*/  dm_segs_dmat; } ;
typedef  int /*<<< orphan*/  bus_dmasync_op_t ;
struct TYPE_5__ {int /*<<< orphan*/  ds_addr; int /*<<< orphan*/  ds_len; } ;
typedef  TYPE_2__ bus_dma_segment_t ;

/* Variables and functions */
 int /*<<< orphan*/  ARCMSR_CDB_FLAG_SGL_BSIZE ; 
 int /*<<< orphan*/  ARCMSR_CDB_FLAG_WRITE ; 
 int /*<<< orphan*/  BUS_DMASYNC_PREREAD ; 
 int /*<<< orphan*/  BUS_DMASYNC_PREWRITE ; 
 int CAM_DIR_IN ; 
 int CAM_DIR_MASK ; 
 scalar_t__ IS_SG64_ADDR ; 
 int /*<<< orphan*/  SRB_FLAG_WRITE ; 
 scalar_t__ arcmsr_htole32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_addr_hi32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_addr_lo32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct ARCMSR_CDB*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  scsiio_cdb_ptr (struct ccb_scsiio*) ; 

__attribute__((used)) static void arcmsr_build_srb(struct CommandControlBlock *srb, 
		bus_dma_segment_t *dm_segs, u_int32_t nseg)
{
	struct ARCMSR_CDB *arcmsr_cdb = &srb->arcmsr_cdb;
	u_int8_t *psge = (u_int8_t *)&arcmsr_cdb->u;
	u_int32_t address_lo, address_hi;
	union ccb *pccb = srb->pccb;
	struct ccb_scsiio *pcsio = &pccb->csio;
	u_int32_t arccdbsize = 0x30;

	memset(arcmsr_cdb, 0, sizeof(struct ARCMSR_CDB));
	arcmsr_cdb->Bus = 0;
	arcmsr_cdb->TargetID = pccb->ccb_h.target_id;
	arcmsr_cdb->LUN = pccb->ccb_h.target_lun;
	arcmsr_cdb->Function = 1;
	arcmsr_cdb->CdbLength = (u_int8_t)pcsio->cdb_len;
	bcopy(scsiio_cdb_ptr(pcsio), arcmsr_cdb->Cdb, pcsio->cdb_len);
	if(nseg != 0) {
		struct AdapterControlBlock *acb = srb->acb;
		bus_dmasync_op_t op;	
		u_int32_t length, i, cdb_sgcount = 0;

		if((pccb->ccb_h.flags & CAM_DIR_MASK) == CAM_DIR_IN) {
			op = BUS_DMASYNC_PREREAD;
		} else {
			op = BUS_DMASYNC_PREWRITE;
			arcmsr_cdb->Flags |= ARCMSR_CDB_FLAG_WRITE;
			srb->srb_flags |= SRB_FLAG_WRITE;
		}
		bus_dmamap_sync(acb->dm_segs_dmat, srb->dm_segs_dmamap, op);
		for(i=0; i < nseg; i++) {
			/* Get the physical address of the current data pointer */
			length = arcmsr_htole32(dm_segs[i].ds_len);
			address_lo = arcmsr_htole32(dma_addr_lo32(dm_segs[i].ds_addr));
			address_hi = arcmsr_htole32(dma_addr_hi32(dm_segs[i].ds_addr));
			if(address_hi == 0) {
				struct SG32ENTRY *pdma_sg = (struct SG32ENTRY *)psge;
				pdma_sg->address = address_lo;
				pdma_sg->length = length;
				psge += sizeof(struct SG32ENTRY);
				arccdbsize += sizeof(struct SG32ENTRY);
			} else {
				u_int32_t sg64s_size = 0, tmplength = length;

				while(1) {
					u_int64_t span4G, length0;
					struct SG64ENTRY *pdma_sg = (struct SG64ENTRY *)psge;

					span4G = (u_int64_t)address_lo + tmplength;
					pdma_sg->addresshigh = address_hi;
					pdma_sg->address = address_lo;
					if(span4G > 0x100000000) {
						/*see if cross 4G boundary*/
						length0 = 0x100000000-address_lo;
						pdma_sg->length = (u_int32_t)length0 | IS_SG64_ADDR;
						address_hi = address_hi+1;
						address_lo = 0;
						tmplength = tmplength - (u_int32_t)length0;
						sg64s_size += sizeof(struct SG64ENTRY);
						psge += sizeof(struct SG64ENTRY);
						cdb_sgcount++;
					} else {
						pdma_sg->length = tmplength | IS_SG64_ADDR;
						sg64s_size += sizeof(struct SG64ENTRY);
						psge += sizeof(struct SG64ENTRY);
						break;
					}
				}
				arccdbsize += sg64s_size;
			}
			cdb_sgcount++;
		}
		arcmsr_cdb->sgcount = (u_int8_t)cdb_sgcount;
		arcmsr_cdb->DataLength = pcsio->dxfer_len;
		if( arccdbsize > 256) {
			arcmsr_cdb->Flags |= ARCMSR_CDB_FLAG_SGL_BSIZE;
		}
	} else {
		arcmsr_cdb->DataLength = 0;
	}
	srb->arc_cdb_size = arccdbsize;
	arcmsr_cdb->msgPages = (arccdbsize/256) + ((arccdbsize % 256) ? 1 : 0);
}