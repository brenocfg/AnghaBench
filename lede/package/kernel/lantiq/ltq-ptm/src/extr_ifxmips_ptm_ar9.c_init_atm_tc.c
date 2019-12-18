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
typedef  int u32 ;

/* Variables and functions */
 int /*<<< orphan*/  DM_RXCB ; 
 int /*<<< orphan*/  DM_RXCFG ; 
 int /*<<< orphan*/  DM_RXDB ; 
 int /*<<< orphan*/  DM_RXPGCNT ; 
 int /*<<< orphan*/  DM_RXPKTCNT ; 
 int /*<<< orphan*/  DS_RXCB ; 
 int /*<<< orphan*/  DS_RXCFG ; 
 int /*<<< orphan*/  DS_RXDB ; 
 int /*<<< orphan*/  DS_RXPGCNT ; 
 int /*<<< orphan*/  FFSM_CFG0 ; 
 int /*<<< orphan*/  FFSM_CFG1 ; 
 int /*<<< orphan*/  FFSM_DBA0 ; 
 int /*<<< orphan*/  FFSM_DBA1 ; 
 int /*<<< orphan*/  FFSM_IDLE_HEAD_BC0 ; 
 int /*<<< orphan*/  FFSM_IDLE_HEAD_BC1 ; 
 int IFX_REG_R32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IFX_REG_W32 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IFX_REG_W32_MASK (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RFBI_CFG ; 
 int /*<<< orphan*/  SFSM_CBA0 ; 
 int /*<<< orphan*/  SFSM_CBA1 ; 
 int /*<<< orphan*/  SFSM_CFG0 ; 
 int /*<<< orphan*/  SFSM_CFG1 ; 
 int /*<<< orphan*/  SFSM_DBA0 ; 
 int /*<<< orphan*/  SFSM_DBA1 ; 
 int /*<<< orphan*/  SW_P2_CTL ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static inline void init_atm_tc(void)
{
    IFX_REG_W32(0x0,        RFBI_CFG);
    IFX_REG_W32(0x1800,     SFSM_DBA0);
    IFX_REG_W32(0x1921,     SFSM_DBA1);
    IFX_REG_W32(0x1A42,     SFSM_CBA0);
    IFX_REG_W32(0x1A53,     SFSM_CBA1);
    IFX_REG_W32(0x14011,    SFSM_CFG0);
    IFX_REG_W32(0x14011,    SFSM_CFG1);
    IFX_REG_W32(0x1000,     FFSM_DBA0);
    IFX_REG_W32(0x1700,     FFSM_DBA1);
    IFX_REG_W32(0x3000C,    FFSM_CFG0);
    IFX_REG_W32(0x3000C,    FFSM_CFG1);
    IFX_REG_W32(0xF0D10000, FFSM_IDLE_HEAD_BC0);
    IFX_REG_W32(0xF0D10000, FFSM_IDLE_HEAD_BC1);

    /*
     *  0. Backup port2 value to temp
     *  1. Disable CPU port2 in switch (link and learning)
     *  2. wait for a while
     *  3. Configure DM register and counter
     *  4. restore temp to CPU port2 in switch
     *  This code will cause network to stop working if there are heavy
     *  traffic during bootup. This part should be moved to switch and use
     *  the same code as ATM
     */
    {
        int i;
        u32 temp;

        temp = IFX_REG_R32(SW_P2_CTL);

        IFX_REG_W32(0x40020000, SW_P2_CTL);
        for (i = 0; i < 200; i++)
            udelay(2000);

        IFX_REG_W32(0x00007028, DM_RXCFG);
        IFX_REG_W32(0x00007028, DS_RXCFG);

        IFX_REG_W32(0x00001100, DM_RXDB);
        IFX_REG_W32(0x00001100, DS_RXDB);

        IFX_REG_W32(0x00001600, DM_RXCB);
        IFX_REG_W32(0x00001600, DS_RXCB);

        /*
         * For dynamic, must reset these counters,
         * For once initialization, don't need to reset these counters
         */
        IFX_REG_W32(0x0, DM_RXPGCNT);
        IFX_REG_W32(0x0, DS_RXPGCNT);
        IFX_REG_W32(0x0, DM_RXPKTCNT);

        IFX_REG_W32_MASK(0, 0x80000000, DM_RXCFG);
        IFX_REG_W32_MASK(0, 0x8000, DS_RXCFG);

        udelay(2000);
        IFX_REG_W32(temp, SW_P2_CTL);
        udelay(2000);
    }
}