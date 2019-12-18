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
typedef  int uint16_t ;
struct bxe_softc {int /*<<< orphan*/  def_att_idx; int /*<<< orphan*/  igu_dsb_id; int /*<<< orphan*/  def_idx; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATTENTION_ID ; 
 int /*<<< orphan*/  BLOGD (struct bxe_softc*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  BLOGE (struct bxe_softc*,char*,int) ; 
 int BXE_DEF_SB_ATT_IDX ; 
 int BXE_DEF_SB_IDX ; 
 int /*<<< orphan*/  DBG_SP ; 
 int /*<<< orphan*/  IGU_INT_ENABLE ; 
 int /*<<< orphan*/  IGU_INT_NOP ; 
 int /*<<< orphan*/  USTORM_ID ; 
 scalar_t__ __predict_false (int) ; 
 int /*<<< orphan*/  bxe_ack_sb (struct bxe_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bxe_attn_int (struct bxe_softc*) ; 
 int /*<<< orphan*/  bxe_eq_int (struct bxe_softc*) ; 
 int bxe_update_dsb_idx (struct bxe_softc*) ; 
 int /*<<< orphan*/  le16toh (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bxe_handle_sp_tq(void *context,
                 int  pending)
{
    struct bxe_softc *sc = (struct bxe_softc *)context;
    uint16_t status;

    BLOGD(sc, DBG_SP, "---> SP TASK <---\n");

    /* what work needs to be performed? */
    status = bxe_update_dsb_idx(sc);

    BLOGD(sc, DBG_SP, "dsb status 0x%04x\n", status);

    /* HW attentions */
    if (status & BXE_DEF_SB_ATT_IDX) {
        BLOGD(sc, DBG_SP, "---> ATTN INTR <---\n");
        bxe_attn_int(sc);
        status &= ~BXE_DEF_SB_ATT_IDX;
    }

    /* SP events: STAT_QUERY and others */
    if (status & BXE_DEF_SB_IDX) {
        /* handle EQ completions */
        BLOGD(sc, DBG_SP, "---> EQ INTR <---\n");
        bxe_eq_int(sc);
        bxe_ack_sb(sc, sc->igu_dsb_id, USTORM_ID,
                   le16toh(sc->def_idx), IGU_INT_NOP, 1);
        status &= ~BXE_DEF_SB_IDX;
    }

    /* if status is non zero then something went wrong */
    if (__predict_false(status)) {
        BLOGE(sc, "Got an unknown SP interrupt! (0x%04x)\n", status);
    }

    /* ack status block only if something was actually handled */
    bxe_ack_sb(sc, sc->igu_dsb_id, ATTENTION_ID,
               le16toh(sc->def_att_idx), IGU_INT_ENABLE, 1);

    /*
     * Must be called after the EQ processing (since eq leads to sriov
     * ramrod completion flows).
     * This flow may have been scheduled by the arrival of a ramrod
     * completion, or by the sriov code rescheduling itself.
     */
    // XXX bxe_iov_sp_task(sc);

}