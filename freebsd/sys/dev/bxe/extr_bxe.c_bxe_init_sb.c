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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct hc_status_block_sm {int dummy; } ;
struct TYPE_5__ {void* lo; void* hi; } ;
struct TYPE_4__ {int vf_id; void* vnic_id; int /*<<< orphan*/  vf_valid; void* pf_id; } ;
struct TYPE_6__ {struct hc_status_block_sm* state_machine; TYPE_2__ host_sb_addr; void* same_igu_sb_1b; TYPE_1__ p_func; void* state; } ;
struct hc_status_block_data_e2 {int /*<<< orphan*/  index_data; TYPE_3__ common; } ;
struct hc_status_block_data_e1x {int /*<<< orphan*/  index_data; TYPE_3__ common; } ;
struct bxe_softc {int dummy; } ;
typedef  int /*<<< orphan*/  bus_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  BLOGD (struct bxe_softc*,int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ CHIP_INT_MODE_IS_BC (struct bxe_softc*) ; 
 int /*<<< orphan*/  CHIP_IS_E1x (struct bxe_softc*) ; 
 int /*<<< orphan*/  DBG_LOAD ; 
 int /*<<< orphan*/  FALSE ; 
 int HC_SEG_ACCESS_NORM ; 
 int IGU_SEG_ACCESS_NORM ; 
 void* SB_ENABLED ; 
 void* SC_FUNC (struct bxe_softc*) ; 
 void* SC_VN (struct bxe_softc*) ; 
 size_t SM_RX_ID ; 
 size_t SM_TX_ID ; 
 void* TRUE ; 
 void* U64_HI (int /*<<< orphan*/ ) ; 
 void* U64_LO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bxe_map_sb_state_machines (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bxe_setup_ndsb_state_machine (struct hc_status_block_sm*,int,int) ; 
 int /*<<< orphan*/  bxe_wr_fp_sb_data (struct bxe_softc*,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  bxe_zero_fp_sb (struct bxe_softc*,int) ; 
 int /*<<< orphan*/  memset (struct hc_status_block_data_e2*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
bxe_init_sb(struct bxe_softc *sc,
            bus_addr_t       busaddr,
            int              vfid,
            uint8_t          vf_valid,
            int              fw_sb_id,
            int              igu_sb_id)
{
    struct hc_status_block_data_e2  sb_data_e2;
    struct hc_status_block_data_e1x sb_data_e1x;
    struct hc_status_block_sm       *hc_sm_p;
    uint32_t *sb_data_p;
    int igu_seg_id;
    int data_size;

    if (CHIP_INT_MODE_IS_BC(sc)) {
        igu_seg_id = HC_SEG_ACCESS_NORM;
    } else {
        igu_seg_id = IGU_SEG_ACCESS_NORM;
    }

    bxe_zero_fp_sb(sc, fw_sb_id);

    if (!CHIP_IS_E1x(sc)) {
        memset(&sb_data_e2, 0, sizeof(struct hc_status_block_data_e2));
        sb_data_e2.common.state = SB_ENABLED;
        sb_data_e2.common.p_func.pf_id = SC_FUNC(sc);
        sb_data_e2.common.p_func.vf_id = vfid;
        sb_data_e2.common.p_func.vf_valid = vf_valid;
        sb_data_e2.common.p_func.vnic_id = SC_VN(sc);
        sb_data_e2.common.same_igu_sb_1b = TRUE;
        sb_data_e2.common.host_sb_addr.hi = U64_HI(busaddr);
        sb_data_e2.common.host_sb_addr.lo = U64_LO(busaddr);
        hc_sm_p = sb_data_e2.common.state_machine;
        sb_data_p = (uint32_t *)&sb_data_e2;
        data_size = (sizeof(struct hc_status_block_data_e2) /
                     sizeof(uint32_t));
        bxe_map_sb_state_machines(sb_data_e2.index_data);
    } else {
        memset(&sb_data_e1x, 0, sizeof(struct hc_status_block_data_e1x));
        sb_data_e1x.common.state = SB_ENABLED;
        sb_data_e1x.common.p_func.pf_id = SC_FUNC(sc);
        sb_data_e1x.common.p_func.vf_id = 0xff;
        sb_data_e1x.common.p_func.vf_valid = FALSE;
        sb_data_e1x.common.p_func.vnic_id = SC_VN(sc);
        sb_data_e1x.common.same_igu_sb_1b = TRUE;
        sb_data_e1x.common.host_sb_addr.hi = U64_HI(busaddr);
        sb_data_e1x.common.host_sb_addr.lo = U64_LO(busaddr);
        hc_sm_p = sb_data_e1x.common.state_machine;
        sb_data_p = (uint32_t *)&sb_data_e1x;
        data_size = (sizeof(struct hc_status_block_data_e1x) /
                     sizeof(uint32_t));
        bxe_map_sb_state_machines(sb_data_e1x.index_data);
    }

    bxe_setup_ndsb_state_machine(&hc_sm_p[SM_RX_ID], igu_sb_id, igu_seg_id);
    bxe_setup_ndsb_state_machine(&hc_sm_p[SM_TX_ID], igu_sb_id, igu_seg_id);

    BLOGD(sc, DBG_LOAD, "Init FW SB %d\n", fw_sb_id);

    /* write indices to HW - PCI guarantees endianity of regpairs */
    bxe_wr_fp_sb_data(sc, fw_sb_id, sb_data_p, data_size);
}