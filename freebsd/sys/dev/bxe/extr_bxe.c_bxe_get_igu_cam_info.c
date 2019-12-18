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
typedef  int uint8_t ;
typedef  int uint32_t ;
struct bxe_softc {int igu_base_sb; int igu_sb_cnt; int igu_dsb_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLOGE (struct bxe_softc*,char*) ; 
 scalar_t__ CHIP_INT_MODE_IS_BC (struct bxe_softc*) ; 
 scalar_t__ CHIP_IS_MODE_4_PORT (struct bxe_softc*) ; 
 int E1HVN_MAX ; 
 int FP_SB_MAX_E1x ; 
 int IGU_FID (int) ; 
 int IGU_FID_ENCODE_IS_PF ; 
 int IGU_FID_PF_NUM_MASK ; 
 scalar_t__ IGU_REG_MAPPING_MEMORY ; 
 int IGU_REG_MAPPING_MEMORY_SIZE ; 
 int IGU_REG_MAPPING_MEMORY_VALID ; 
 scalar_t__ IGU_VEC (int) ; 
 int REG_RD (struct bxe_softc*,scalar_t__) ; 
 int SC_FUNC (struct bxe_softc*) ; 
 int SC_VN (struct bxe_softc*) ; 
 int min (int,int) ; 

__attribute__((used)) static int
bxe_get_igu_cam_info(struct bxe_softc *sc)
{
    int pfid = SC_FUNC(sc);
    int igu_sb_id;
    uint32_t val;
    uint8_t fid, igu_sb_cnt = 0;

    sc->igu_base_sb = 0xff;

    if (CHIP_INT_MODE_IS_BC(sc)) {
        int vn = SC_VN(sc);
        igu_sb_cnt = sc->igu_sb_cnt;
        sc->igu_base_sb = ((CHIP_IS_MODE_4_PORT(sc) ? pfid : vn) *
                           FP_SB_MAX_E1x);
        sc->igu_dsb_id = (E1HVN_MAX * FP_SB_MAX_E1x +
                          (CHIP_IS_MODE_4_PORT(sc) ? pfid : vn));
        return (0);
    }

    /* IGU in normal mode - read CAM */
    for (igu_sb_id = 0;
         igu_sb_id < IGU_REG_MAPPING_MEMORY_SIZE;
         igu_sb_id++) {
        val = REG_RD(sc, IGU_REG_MAPPING_MEMORY + igu_sb_id * 4);
        if (!(val & IGU_REG_MAPPING_MEMORY_VALID)) {
            continue;
        }
        fid = IGU_FID(val);
        if ((fid & IGU_FID_ENCODE_IS_PF)) {
            if ((fid & IGU_FID_PF_NUM_MASK) != pfid) {
                continue;
            }
            if (IGU_VEC(val) == 0) {
                /* default status block */
                sc->igu_dsb_id = igu_sb_id;
            } else {
                if (sc->igu_base_sb == 0xff) {
                    sc->igu_base_sb = igu_sb_id;
                }
                igu_sb_cnt++;
            }
        }
    }

    /*
     * Due to new PF resource allocation by MFW T7.4 and above, it's optional
     * that number of CAM entries will not be equal to the value advertised in
     * PCI. Driver should use the minimal value of both as the actual status
     * block count
     */
    sc->igu_sb_cnt = min(sc->igu_sb_cnt, igu_sb_cnt);

    if (igu_sb_cnt == 0) {
        BLOGE(sc, "CAM configuration error\n");
        return (-1);
    }

    return (0);
}