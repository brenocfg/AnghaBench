#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int uint32_t ;
struct bxe_softc {int fw_seq; } ;
struct TYPE_2__ {int /*<<< orphan*/  fw_mb_header; int /*<<< orphan*/  drv_mb_header; int /*<<< orphan*/  drv_mb_param; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLOGD (struct bxe_softc*,int /*<<< orphan*/ ,char*,int,int,...) ; 
 int /*<<< orphan*/  BLOGE (struct bxe_softc*,char*) ; 
 int /*<<< orphan*/  BXE_FWMB_LOCK (struct bxe_softc*) ; 
 int /*<<< orphan*/  BXE_FWMB_UNLOCK (struct bxe_softc*) ; 
 scalar_t__ CHIP_REV_IS_SLOW (struct bxe_softc*) ; 
 int /*<<< orphan*/  DBG_PHY ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int FW_MSG_CODE_MASK ; 
 int FW_MSG_SEQ_NUMBER_MASK ; 
 int SC_FW_MB_IDX (struct bxe_softc*) ; 
 int SHMEM_RD (struct bxe_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SHMEM_WR (struct bxe_softc*,int /*<<< orphan*/ ,int) ; 
 TYPE_1__* func_mb ; 

uint32_t
elink_cb_fw_command(struct bxe_softc *sc,
                    uint32_t         command,
                    uint32_t         param)
{
    int mb_idx = SC_FW_MB_IDX(sc);
    uint32_t seq;
    uint32_t rc = 0;
    uint32_t cnt = 1;
    uint8_t delay = CHIP_REV_IS_SLOW(sc) ? 100 : 10;

    BXE_FWMB_LOCK(sc);

    seq = ++sc->fw_seq;
    SHMEM_WR(sc, func_mb[mb_idx].drv_mb_param, param);
    SHMEM_WR(sc, func_mb[mb_idx].drv_mb_header, (command | seq));

    BLOGD(sc, DBG_PHY,
          "wrote command 0x%08x to FW MB param 0x%08x\n",
          (command | seq), param);

    /* Let the FW do it's magic. GIve it up to 5 seconds... */
    do {
        DELAY(delay * 1000);
        rc = SHMEM_RD(sc, func_mb[mb_idx].fw_mb_header);
    } while ((seq != (rc & FW_MSG_SEQ_NUMBER_MASK)) && (cnt++ < 500));

    BLOGD(sc, DBG_PHY,
          "[after %d ms] read 0x%x seq 0x%x from FW MB\n",
          cnt*delay, rc, seq);

    /* is this a reply to our command? */
    if (seq == (rc & FW_MSG_SEQ_NUMBER_MASK)) {
        rc &= FW_MSG_CODE_MASK;
    } else {
        /* Ruh-roh! */
        BLOGE(sc, "FW failed to respond!\n");
        // XXX bxe_fw_dump(sc);
        rc = 0;
    }

    BXE_FWMB_UNLOCK(sc);
    return (rc);
}