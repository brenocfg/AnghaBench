#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
typedef  scalar_t__ t_Handle ;
struct TYPE_6__ {int majorRev; } ;
struct TYPE_7__ {int /*<<< orphan*/  macId; int /*<<< orphan*/  h_Fm; TYPE_1__ fmRevInfo; } ;
struct TYPE_8__ {int /*<<< orphan*/  h_App; int /*<<< orphan*/  (* f_Exception ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;TYPE_2__ fmMacControllerDriver; struct dtsec_regs* p_MemMap; } ;
typedef  TYPE_3__ t_Dtsec ;
struct dtsec_regs {int tpkt; int rctrl; int ievent; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_COND (int) ; 
 int /*<<< orphan*/  DBG (int /*<<< orphan*/ ,char*) ; 
 int DTSEC_IMASK_ABRTEN ; 
 int DTSEC_IMASK_BREN ; 
 int DTSEC_IMASK_BTEN ; 
 int DTSEC_IMASK_CRLEN ; 
 int DTSEC_IMASK_GRSCEN ; 
 int DTSEC_IMASK_GTSCEN ; 
 int DTSEC_IMASK_IFERREN ; 
 int DTSEC_IMASK_LCEN ; 
 int DTSEC_IMASK_MAGEN ; 
 int DTSEC_IMASK_MMRDEN ; 
 int DTSEC_IMASK_MMWREN ; 
 int DTSEC_IMASK_MSROEN ; 
 int DTSEC_IMASK_RDPEEN ; 
 int DTSEC_IMASK_RXCEN ; 
 int DTSEC_IMASK_TDPEEN ; 
 int DTSEC_IMASK_TXCEN ; 
 int DTSEC_IMASK_TXEEN ; 
 int DTSEC_IMASK_XFUNEN ; 
 int DtsecGetMaxFrameLength (TYPE_3__*) ; 
 int /*<<< orphan*/  FmResetMac (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int GET_UINT32 (int) ; 
 int /*<<< orphan*/  INFO ; 
 scalar_t__ MIN (int,int) ; 
 int RCTRL_GRS ; 
 int /*<<< orphan*/  UpdateStatistics (TYPE_3__*) ; 
 int /*<<< orphan*/  WRITE_UINT32 (int,int) ; 
 int /*<<< orphan*/  XX_UDelay (int) ; 
 int /*<<< orphan*/  e_FM_MAC_1G ; 
 int /*<<< orphan*/  e_FM_MAC_EX_1G_BAB_RX ; 
 int /*<<< orphan*/  e_FM_MAC_EX_1G_BAB_TX ; 
 int /*<<< orphan*/  e_FM_MAC_EX_1G_COL_RET_LMT ; 
 int /*<<< orphan*/  e_FM_MAC_EX_1G_GRATEFUL_RX_STP_COMPLET ; 
 int /*<<< orphan*/  e_FM_MAC_EX_1G_GRATEFUL_TX_STP_COMPLET ; 
 int /*<<< orphan*/  e_FM_MAC_EX_1G_LATE_COL ; 
 int /*<<< orphan*/  e_FM_MAC_EX_1G_MAG_PCKT ; 
 int /*<<< orphan*/  e_FM_MAC_EX_1G_RX_CTL ; 
 int /*<<< orphan*/  e_FM_MAC_EX_1G_RX_DATA_ERR ; 
 int /*<<< orphan*/  e_FM_MAC_EX_1G_TX_CTL ; 
 int /*<<< orphan*/  e_FM_MAC_EX_1G_TX_DATA_ERR ; 
 int /*<<< orphan*/  e_FM_MAC_EX_1G_TX_ERR ; 
 int /*<<< orphan*/  e_FM_MAC_EX_1G_TX_FIFO_UNDRN ; 
 int /*<<< orphan*/  fman_dtsec_ack_event (struct dtsec_regs*,int) ; 
 int fman_dtsec_get_event (struct dtsec_regs*,int) ; 
 int fman_dtsec_get_interrupt_mask (struct dtsec_regs*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub10 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub11 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub12 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub13 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub5 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub6 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub7 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub8 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub9 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void DtsecIsr(t_Handle h_Dtsec)
{
    t_Dtsec             *p_Dtsec = (t_Dtsec *)h_Dtsec;
    uint32_t            event;
    struct dtsec_regs   *p_DtsecMemMap = p_Dtsec->p_MemMap;

    /* do not handle MDIO events */
    event = fman_dtsec_get_event(p_DtsecMemMap, (uint32_t)(~(DTSEC_IMASK_MMRDEN | DTSEC_IMASK_MMWREN)));

    event &= fman_dtsec_get_interrupt_mask(p_DtsecMemMap);

    fman_dtsec_ack_event(p_DtsecMemMap, event);

    if (event & DTSEC_IMASK_BREN)
        p_Dtsec->f_Exception(p_Dtsec->h_App, e_FM_MAC_EX_1G_BAB_RX);
    if (event & DTSEC_IMASK_RXCEN)
        p_Dtsec->f_Exception(p_Dtsec->h_App, e_FM_MAC_EX_1G_RX_CTL);
    if (event & DTSEC_IMASK_MSROEN)
        UpdateStatistics(p_Dtsec);
    if (event & DTSEC_IMASK_GTSCEN)
        p_Dtsec->f_Exception(p_Dtsec->h_App, e_FM_MAC_EX_1G_GRATEFUL_TX_STP_COMPLET);
    if (event & DTSEC_IMASK_BTEN)
        p_Dtsec->f_Exception(p_Dtsec->h_App, e_FM_MAC_EX_1G_BAB_TX);
    if (event & DTSEC_IMASK_TXCEN)
        p_Dtsec->f_Exception(p_Dtsec->h_App, e_FM_MAC_EX_1G_TX_CTL);
    if (event & DTSEC_IMASK_TXEEN)
        p_Dtsec->f_Exception(p_Dtsec->h_App, e_FM_MAC_EX_1G_TX_ERR);
    if (event & DTSEC_IMASK_LCEN)
        p_Dtsec->f_Exception(p_Dtsec->h_App, e_FM_MAC_EX_1G_LATE_COL);
    if (event & DTSEC_IMASK_CRLEN)
        p_Dtsec->f_Exception(p_Dtsec->h_App, e_FM_MAC_EX_1G_COL_RET_LMT);
    if (event & DTSEC_IMASK_XFUNEN)
    {
#ifdef FM_TX_LOCKUP_ERRATA_DTSEC6
        if (p_Dtsec->fmMacControllerDriver.fmRevInfo.majorRev == 2)
        {
            uint32_t  tpkt1, tmpReg1, tpkt2, tmpReg2, i;
            /* a. Write 0x00E0_0C00 to DTSEC_ID */
            /* This is a read only regidter */

            /* b. Read and save the value of TPKT */
            tpkt1 = GET_UINT32(p_DtsecMemMap->tpkt);

            /* c. Read the register at dTSEC address offset 0x32C */
            tmpReg1 =  GET_UINT32(*(uint32_t*)((uint8_t*)p_DtsecMemMap + 0x32c));

            /* d. Compare bits [9:15] to bits [25:31] of the register at address offset 0x32C. */
            if ((tmpReg1 & 0x007F0000) != (tmpReg1 & 0x0000007F))
            {
                /* If they are not equal, save the value of this register and wait for at least
                 * MAXFRM*16 ns */
                XX_UDelay((uint32_t)(MIN(DtsecGetMaxFrameLength(p_Dtsec)*16/1000, 1)));
            }

            /* e. Read and save TPKT again and read the register at dTSEC address offset
                0x32C again*/
            tpkt2 = GET_UINT32(p_DtsecMemMap->tpkt);
            tmpReg2 = GET_UINT32(*(uint32_t*)((uint8_t*)p_DtsecMemMap + 0x32c));

            /* f. Compare the value of TPKT saved in step b to value read in step e. Also
                compare bits [9:15] of the register at offset 0x32C saved in step d to the value
                of bits [9:15] saved in step e. If the two registers values are unchanged, then
                the transmit portion of the dTSEC controller is locked up and the user should
                proceed to the recover sequence. */
            if ((tpkt1 == tpkt2) && ((tmpReg1 & 0x007F0000) == (tmpReg2 & 0x007F0000)))
            {
                /* recover sequence */

                /* a.Write a 1 to RCTRL[GRS]*/

                WRITE_UINT32(p_DtsecMemMap->rctrl, GET_UINT32(p_DtsecMemMap->rctrl) | RCTRL_GRS);

                /* b.Wait until IEVENT[GRSC]=1, or at least 100 us has elapsed. */
                for (i = 0 ; i < 100 ; i++ )
                {
                    if (GET_UINT32(p_DtsecMemMap->ievent) & DTSEC_IMASK_GRSCEN)
                        break;
                    XX_UDelay(1);
                }
                if (GET_UINT32(p_DtsecMemMap->ievent) & DTSEC_IMASK_GRSCEN)
                    WRITE_UINT32(p_DtsecMemMap->ievent, DTSEC_IMASK_GRSCEN);
                else
                    DBG(INFO,("Rx lockup due to dTSEC Tx lockup"));

                /* c.Write a 1 to bit n of FM_RSTC (offset 0x0CC of FPM)*/
                FmResetMac(p_Dtsec->fmMacControllerDriver.h_Fm, e_FM_MAC_1G, p_Dtsec->fmMacControllerDriver.macId);

                /* d.Wait 4 Tx clocks (32 ns) */
                XX_UDelay(1);

                /* e.Write a 0 to bit n of FM_RSTC. */
                /* cleared by FMAN */
            }
        }
#endif /* FM_TX_LOCKUP_ERRATA_DTSEC6 */

        p_Dtsec->f_Exception(p_Dtsec->h_App, e_FM_MAC_EX_1G_TX_FIFO_UNDRN);
    }
    if (event & DTSEC_IMASK_MAGEN)
        p_Dtsec->f_Exception(p_Dtsec->h_App, e_FM_MAC_EX_1G_MAG_PCKT);
    if (event & DTSEC_IMASK_GRSCEN)
        p_Dtsec->f_Exception(p_Dtsec->h_App, e_FM_MAC_EX_1G_GRATEFUL_RX_STP_COMPLET);
    if (event & DTSEC_IMASK_TDPEEN)
        p_Dtsec->f_Exception(p_Dtsec->h_App, e_FM_MAC_EX_1G_TX_DATA_ERR);
    if (event & DTSEC_IMASK_RDPEEN)
        p_Dtsec->f_Exception(p_Dtsec->h_App, e_FM_MAC_EX_1G_RX_DATA_ERR);

    /*  - masked interrupts */
    ASSERT_COND(!(event & DTSEC_IMASK_ABRTEN));
    ASSERT_COND(!(event & DTSEC_IMASK_IFERREN));
}