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
struct TYPE_3__ {void* vf_valid; } ;
struct TYPE_4__ {TYPE_1__ p_func; void* state; } ;
struct hc_status_block_data_e2 {TYPE_2__ common; } ;
struct hc_status_block_data_e1x {TYPE_2__ common; } ;
struct bxe_softc {int dummy; } ;

/* Variables and functions */
 scalar_t__ BAR_CSTRORM_INTMEM ; 
 int /*<<< orphan*/  CHIP_IS_E1x (struct bxe_softc*) ; 
 scalar_t__ CSTORM_STATUS_BLOCK_OFFSET (int) ; 
 int /*<<< orphan*/  CSTORM_STATUS_BLOCK_SIZE ; 
 scalar_t__ CSTORM_SYNC_BLOCK_OFFSET (int) ; 
 int /*<<< orphan*/  CSTORM_SYNC_BLOCK_SIZE ; 
 void* FALSE ; 
 void* SB_DISABLED ; 
 int /*<<< orphan*/  bxe_fill (struct bxe_softc*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bxe_wr_fp_sb_data (struct bxe_softc*,int,int*,int) ; 
 int /*<<< orphan*/  memset (struct hc_status_block_data_e2*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
bxe_zero_fp_sb(struct bxe_softc *sc,
               int              fw_sb_id)
{
    struct hc_status_block_data_e2 sb_data_e2;
    struct hc_status_block_data_e1x sb_data_e1x;
    uint32_t *sb_data_p;
    uint32_t data_size = 0;

    if (!CHIP_IS_E1x(sc)) {
        memset(&sb_data_e2, 0, sizeof(struct hc_status_block_data_e2));
        sb_data_e2.common.state = SB_DISABLED;
        sb_data_e2.common.p_func.vf_valid = FALSE;
        sb_data_p = (uint32_t *)&sb_data_e2;
        data_size = (sizeof(struct hc_status_block_data_e2) /
                     sizeof(uint32_t));
    } else {
        memset(&sb_data_e1x, 0, sizeof(struct hc_status_block_data_e1x));
        sb_data_e1x.common.state = SB_DISABLED;
        sb_data_e1x.common.p_func.vf_valid = FALSE;
        sb_data_p = (uint32_t *)&sb_data_e1x;
        data_size = (sizeof(struct hc_status_block_data_e1x) /
                     sizeof(uint32_t));
    }

    bxe_wr_fp_sb_data(sc, fw_sb_id, sb_data_p, data_size);

    bxe_fill(sc, (BAR_CSTRORM_INTMEM + CSTORM_STATUS_BLOCK_OFFSET(fw_sb_id)),
             0, CSTORM_STATUS_BLOCK_SIZE);
    bxe_fill(sc, (BAR_CSTRORM_INTMEM + CSTORM_SYNC_BLOCK_OFFSET(fw_sb_id)),
             0, CSTORM_SYNC_BLOCK_SIZE);
}