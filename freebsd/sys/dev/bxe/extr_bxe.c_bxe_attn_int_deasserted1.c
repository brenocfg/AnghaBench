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
typedef  int uint32_t ;
struct bxe_softc {int /*<<< orphan*/  sp_err_timeout_task; } ;
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
 int AEU_INPUTS_ATTN_BITS_DOORBELLQ_HW_INTERRUPT ; 
 int /*<<< orphan*/  BLOGE (struct bxe_softc*,char*,...) ; 
 int /*<<< orphan*/  BXE_ERR_MISC ; 
 int /*<<< orphan*/  BXE_SET_ERROR_BIT (struct bxe_softc*,int /*<<< orphan*/ ) ; 
 int DORQ_REG_DORQ_INT_STS_CLR ; 
 scalar_t__ FALSE ; 
 int HW_INTERRUT_ASSERT_SET_1 ; 
 int MISC_REG_AEU_ENABLE1_FUNC_0_OUT_1 ; 
 int MISC_REG_AEU_ENABLE1_FUNC_1_OUT_1 ; 
 int REG_RD (struct bxe_softc*,int) ; 
 int /*<<< orphan*/  REG_WR (struct bxe_softc*,int,int) ; 
 int SC_PORT (struct bxe_softc*) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  bxe_panic (struct bxe_softc*,char*) ; 
 int hz ; 
 int /*<<< orphan*/  taskqueue_enqueue_timeout (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  taskqueue_thread ; 

__attribute__((used)) static void
bxe_attn_int_deasserted1(struct bxe_softc *sc,
                         uint32_t         attn)
{
    int port = SC_PORT(sc);
    int reg_offset;
    uint32_t val;
    boolean_t err_flg = FALSE;

    if (attn & AEU_INPUTS_ATTN_BITS_DOORBELLQ_HW_INTERRUPT) {
        val = REG_RD(sc, DORQ_REG_DORQ_INT_STS_CLR);
        BLOGE(sc, "DB hw attention 0x%08x\n", val);
        /* DORQ discard attention */
        if (val & 0x2) {
            BLOGE(sc, "FATAL error from DORQ\n");
	    err_flg = TRUE;
        }
    }

    if (attn & HW_INTERRUT_ASSERT_SET_1) {
        reg_offset = (port ? MISC_REG_AEU_ENABLE1_FUNC_1_OUT_1 :
                             MISC_REG_AEU_ENABLE1_FUNC_0_OUT_1);

        val = REG_RD(sc, reg_offset);
        val &= ~(attn & HW_INTERRUT_ASSERT_SET_1);
        REG_WR(sc, reg_offset, val);

        BLOGE(sc, "FATAL HW block attention set1 0x%08x\n",
              (uint32_t)(attn & HW_INTERRUT_ASSERT_SET_1));
        err_flg = TRUE;
        bxe_panic(sc, ("HW block attention set1\n"));
    }
    if(err_flg) {
        BXE_SET_ERROR_BIT(sc, BXE_ERR_MISC);
        taskqueue_enqueue_timeout(taskqueue_thread,
           &sc->sp_err_timeout_task, hz/10);
    }

}