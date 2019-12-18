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
typedef  scalar_t__ uint32_t ;
struct bxe_softc {int dummy; } ;

/* Variables and functions */
 int BCM_5710_FW_ENGINEERING_VERSION ; 
 scalar_t__ BCM_5710_FW_MAJOR_VERSION ; 
 int BCM_5710_FW_MINOR_VERSION ; 
 int BCM_5710_FW_REVISION_VERSION ; 
 int /*<<< orphan*/  BLOGD (struct bxe_softc*,int /*<<< orphan*/ ,char*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  BLOGE (struct bxe_softc*,char*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  DBG_LOAD ; 
 scalar_t__ FW_MSG_CODE_DRV_LOAD_COMMON ; 
 scalar_t__ FW_MSG_CODE_DRV_LOAD_COMMON_CHIP ; 
 scalar_t__ REG_RD (struct bxe_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XSEM_REG_PRAM ; 

__attribute__((used)) static int
bxe_nic_load_analyze_req(struct bxe_softc *sc,
                         uint32_t         load_code)
{
    uint32_t my_fw, loaded_fw;

    /* is another pf loaded on this engine? */
    if ((load_code != FW_MSG_CODE_DRV_LOAD_COMMON_CHIP) &&
        (load_code != FW_MSG_CODE_DRV_LOAD_COMMON)) {
        /* build my FW version dword */
        my_fw = (BCM_5710_FW_MAJOR_VERSION +
                 (BCM_5710_FW_MINOR_VERSION << 8 ) +
                 (BCM_5710_FW_REVISION_VERSION << 16) +
                 (BCM_5710_FW_ENGINEERING_VERSION << 24));

        /* read loaded FW from chip */
        loaded_fw = REG_RD(sc, XSEM_REG_PRAM);
        BLOGD(sc, DBG_LOAD, "loaded FW 0x%08x / my FW 0x%08x\n",
              loaded_fw, my_fw);

        /* abort nic load if version mismatch */
        if (my_fw != loaded_fw) {
            BLOGE(sc, "FW 0x%08x already loaded (mine is 0x%08x)",
                  loaded_fw, my_fw);
            return (-1);
        }
    }

    return (0);
}