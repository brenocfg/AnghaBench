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
typedef  int u_int32_t ;
typedef  int u_int16_t ;
struct InBound_SRB {int length; int /*<<< orphan*/  addressLow; int /*<<< orphan*/  addressHigh; } ;
struct HBD_MessageUnit0 {int postq_index; int /*<<< orphan*/ * post_qbuffer; } ;
struct HBB_MessageUnit {int postq_index; int* post_qbuffer; int /*<<< orphan*/  drv2iop_doorbell; } ;
struct CommandControlBlock {int srb_flags; int arc_cdb_size; int smid; int /*<<< orphan*/  cdb_phyaddr_low; int /*<<< orphan*/  cdb_phyaddr_high; int /*<<< orphan*/  srb_state; int /*<<< orphan*/  arcmsr_cdb; } ;
struct TYPE_3__ {int phyadd_high; } ;
struct TYPE_4__ {TYPE_1__ B; } ;
struct AdapterControlBlock {int adapter_type; int /*<<< orphan*/  postDone_lock; scalar_t__ pmu; TYPE_2__ srb_phyaddr; int /*<<< orphan*/  srboutstandingcount; int /*<<< orphan*/  srb_dmamap; int /*<<< orphan*/  srb_dmat; } ;
struct ARCMSR_CDB {int Flags; int /*<<< orphan*/  Context; } ;

/* Variables and functions */
#define  ACB_ADAPTER_TYPE_A 132 
#define  ACB_ADAPTER_TYPE_B 131 
#define  ACB_ADAPTER_TYPE_C 130 
#define  ACB_ADAPTER_TYPE_D 129 
#define  ACB_ADAPTER_TYPE_E 128 
 int ARCMSR_CDB_FLAG_SGL_BSIZE ; 
 int /*<<< orphan*/  ARCMSR_DRV2IOP_CDB_POSTED ; 
 int /*<<< orphan*/  ARCMSR_LOCK_ACQUIRE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ARCMSR_LOCK_RELEASE (int /*<<< orphan*/ *) ; 
 int ARCMSR_MAX_HBB_POSTQUEUE ; 
 int ARCMSR_MAX_HBD_POSTQUEUE ; 
 int ARCMSR_SRBPOST_FLAG_SGL_BSIZE ; 
 int /*<<< orphan*/  ARCMSR_SRB_START ; 
 int /*<<< orphan*/  BUS_DMASYNC_POSTREAD ; 
 int /*<<< orphan*/  BUS_DMASYNC_POSTWRITE ; 
 int /*<<< orphan*/  CHIP_REG_WRITE32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HBA_MessageUnit ; 
 int /*<<< orphan*/  HBC_MessageUnit ; 
 int /*<<< orphan*/  HBD_MessageUnit ; 
 int /*<<< orphan*/  HBE_MessageUnit ; 
 int SRB_FLAG_WRITE ; 
 int /*<<< orphan*/  WRITE_CHIP_REG32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_add_int (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inbound_queueport ; 
 int /*<<< orphan*/  inbound_queueport_high ; 
 int /*<<< orphan*/  inbound_queueport_low ; 
 int /*<<< orphan*/  inboundlist_write_pointer ; 

__attribute__((used)) static void arcmsr_post_srb(struct AdapterControlBlock *acb, struct CommandControlBlock *srb)
{
	u_int32_t cdb_phyaddr_low = (u_int32_t) srb->cdb_phyaddr_low;
	struct ARCMSR_CDB *arcmsr_cdb = (struct ARCMSR_CDB *)&srb->arcmsr_cdb;

	bus_dmamap_sync(acb->srb_dmat, acb->srb_dmamap, (srb->srb_flags & SRB_FLAG_WRITE) ? BUS_DMASYNC_POSTWRITE:BUS_DMASYNC_POSTREAD);
	atomic_add_int(&acb->srboutstandingcount, 1);
	srb->srb_state = ARCMSR_SRB_START;

	switch (acb->adapter_type) {
	case ACB_ADAPTER_TYPE_A: {
			if(arcmsr_cdb->Flags & ARCMSR_CDB_FLAG_SGL_BSIZE) {
				CHIP_REG_WRITE32(HBA_MessageUnit, 0, inbound_queueport, cdb_phyaddr_low|ARCMSR_SRBPOST_FLAG_SGL_BSIZE);
			} else {
				CHIP_REG_WRITE32(HBA_MessageUnit, 0, inbound_queueport, cdb_phyaddr_low);
			}
		}
		break;
	case ACB_ADAPTER_TYPE_B: {
			struct HBB_MessageUnit *phbbmu = (struct HBB_MessageUnit *)acb->pmu;
			int ending_index, index;

			index = phbbmu->postq_index;
			ending_index = ((index+1) % ARCMSR_MAX_HBB_POSTQUEUE);
			phbbmu->post_qbuffer[ending_index] = 0;
			if(arcmsr_cdb->Flags & ARCMSR_CDB_FLAG_SGL_BSIZE) {
				phbbmu->post_qbuffer[index] = cdb_phyaddr_low | ARCMSR_SRBPOST_FLAG_SGL_BSIZE;
			} else {
				phbbmu->post_qbuffer[index] = cdb_phyaddr_low;
			}
			index++;
			index %= ARCMSR_MAX_HBB_POSTQUEUE;     /*if last index number set it to 0 */
			phbbmu->postq_index = index;
			WRITE_CHIP_REG32(0, phbbmu->drv2iop_doorbell, ARCMSR_DRV2IOP_CDB_POSTED);
		}
		break;
	case ACB_ADAPTER_TYPE_C: {
			u_int32_t ccb_post_stamp, arc_cdb_size, cdb_phyaddr_hi32;

			arc_cdb_size = (srb->arc_cdb_size > 0x300) ? 0x300 : srb->arc_cdb_size;
			ccb_post_stamp = (cdb_phyaddr_low | ((arc_cdb_size-1) >> 6) | 1);
			cdb_phyaddr_hi32 = acb->srb_phyaddr.B.phyadd_high;
			if(cdb_phyaddr_hi32)
			{
				CHIP_REG_WRITE32(HBC_MessageUnit,0,inbound_queueport_high, cdb_phyaddr_hi32);
				CHIP_REG_WRITE32(HBC_MessageUnit,0,inbound_queueport_low, ccb_post_stamp);
			}
			else
			{
				CHIP_REG_WRITE32(HBC_MessageUnit,0,inbound_queueport_low, ccb_post_stamp);
			}
		}
		break;
	case ACB_ADAPTER_TYPE_D: {
			struct HBD_MessageUnit0 *phbdmu = (struct HBD_MessageUnit0 *)acb->pmu;
			u_int16_t index_stripped;
			u_int16_t postq_index;
			struct InBound_SRB *pinbound_srb;

			ARCMSR_LOCK_ACQUIRE(&acb->postDone_lock);
			postq_index = phbdmu->postq_index;
			pinbound_srb = (struct InBound_SRB *)&phbdmu->post_qbuffer[postq_index & 0xFF];
			pinbound_srb->addressHigh = srb->cdb_phyaddr_high;
			pinbound_srb->addressLow = srb->cdb_phyaddr_low;
			pinbound_srb->length = srb->arc_cdb_size >> 2;
			arcmsr_cdb->Context = srb->cdb_phyaddr_low;
			if (postq_index & 0x4000) {
				index_stripped = postq_index & 0xFF;
				index_stripped += 1;
				index_stripped %= ARCMSR_MAX_HBD_POSTQUEUE;
				phbdmu->postq_index = index_stripped ? (index_stripped | 0x4000) : index_stripped;
			} else {
				index_stripped = postq_index;
				index_stripped += 1;
				index_stripped %= ARCMSR_MAX_HBD_POSTQUEUE;
				phbdmu->postq_index = index_stripped ? index_stripped : (index_stripped | 0x4000);
			}
			CHIP_REG_WRITE32(HBD_MessageUnit, 0, inboundlist_write_pointer, postq_index);
			ARCMSR_LOCK_RELEASE(&acb->postDone_lock);
		}
		break;
	case ACB_ADAPTER_TYPE_E: {
			u_int32_t ccb_post_stamp, arc_cdb_size;

			arc_cdb_size = (srb->arc_cdb_size > 0x300) ? 0x300 : srb->arc_cdb_size;
			ccb_post_stamp = (srb->smid | ((arc_cdb_size-1) >> 6));
			CHIP_REG_WRITE32(HBE_MessageUnit, 0, inbound_queueport_high, 0);
			CHIP_REG_WRITE32(HBE_MessageUnit, 0, inbound_queueport_low, ccb_post_stamp);
        	}
		break;
	}
}