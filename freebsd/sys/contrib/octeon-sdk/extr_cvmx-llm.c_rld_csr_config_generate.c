#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_5__ {int dfa_memcfg0_base; int dfa_memcfg1_base; int mrs_dat_p0bunk0; int mrs_dat_p1bunk0; int mrs_dat_p0bunk1; int mrs_dat_p1bunk1; int p0_ena; int p1_ena; int bunkport; } ;
typedef  TYPE_1__ rldram_csr_config_t ;
struct TYPE_6__ {char* addr_rld0_fb_str; char* addr_rld0_bb_str; char* addr_rld1_fb_str; char* addr_rld1_bb_str; int rld1_bunks; int rld0_bunks; int rld0_mbytes; int rld1_mbytes; int cpu_hz; int max_rld_clock_mhz; } ;
typedef  TYPE_2__ llm_descriptor_t ;

/* Variables and functions */
 int MIN (int,int) ; 
 int /*<<< orphan*/  OCTEON_CN58XX ; 
 scalar_t__ OCTEON_IS_MODEL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cvmx_dprintf (char*,...) ; 
 int process_address_map_str (int,char*) ; 
 int tskw_mod ; 
 int tskw_ps ; 

int rld_csr_config_generate(llm_descriptor_t *llm_desc_ptr, rldram_csr_config_t *cfg_ptr)
{
    char *addr_rld0_fb_str;
    char *addr_rld0_bb_str;
    char *addr_rld1_fb_str;
    char *addr_rld1_bb_str;
    int eclk_ps;
    int mtype = 0;                           // MTYPE (0: RLDRAM/1: FCRAM
    int trcmin = 20;                         // tRC(min) - from RLDRAM data sheet
    int trc_cyc;                             // TRC(cyc)
    int trc_mod;
    int trl_cyc;                             // TRL(cyc)
    int twl_cyc;                             // TWL(cyc)
    int tmrsc_cyc = 6;                       // tMRSC(cyc)  [2-7]
    int mclk_ps;                             // DFA Memory Clock(in ps) = 2x eclk
    int rldcfg = 99;                         // RLDRAM-II CFG (1,2,3)
    int mrs_odt = 0;                         // RLDRAM MRS A[9]=ODT (default)
    int mrs_impmatch = 0;                    // RLDRAM MRS A[8]=Impedance Matching (default)
    int mrs_dllrst = 1;                      // RLDRAM MRS A[7]=DLL Reset (default)
    uint32_t mrs_dat;
    int mrs_dat_p0bunk0 = 0;                 // MRS Register Data After Address Map (for Port0 Bunk0)
    int mrs_dat_p0bunk1 = 0;                 // MRS Register Data After Address Map (for Port0 Bunk1)
    int mrs_dat_p1bunk0 = 0;                 // MRS Register Data After Address Map (for Port1 Bunk0)
    int mrs_dat_p1bunk1 = 0;                 // MRS Register Data After Address Map (for Port1 Bunk1)
    int p0_ena = 0;                          // DFA Port#0 Enabled
    int p1_ena = 0;                          // DFA Port#1 Enabled
    int memport = 0;                       // Memory(MB) per Port [MAX=512]
    int membunk;                             // Memory(MB) per Bunk
    int bunkport = 0;                        // Bunks/Port [1/2]
    int pbunk = 0;                               // Physical Bunk(or Rank) encoding for address bit
    int tref_ms = 32;                        // tREF(ms) (RLDRAM-II overall device refresh interval
    int trefi_ns;                            // tREFI(ns) = tREF(ns)/#rows/bank
    int rows = 8;                            // #rows/bank (K) typically 8K
    int ref512int;
    int ref512mod;
    int tskw_cyc = 0;
    int fprch = 1;
    int bprch = 0;
    int dfa_memcfg0_base = 0;
    int dfa_memcfg1_base = 0;
    int tbl = 1;                             // tBL (1: 2-burst /2: 4-burst)
    int rw_dly;
    int wr_dly;
    int r2r = 1;
    int sil_lat = 1;
    int clkdiv = 2;  /* CN38XX is fixed at 2, CN58XX supports 2,3,4 */
    int clkdiv_enc = 0x0;  /* Encoded clock divisor, only used for CN58XX */

    if (!llm_desc_ptr)
        return -1;

    /* Setup variables from descriptor */

    addr_rld0_fb_str = llm_desc_ptr->addr_rld0_fb_str;
    addr_rld0_bb_str = llm_desc_ptr->addr_rld0_bb_str;
    addr_rld1_fb_str = llm_desc_ptr->addr_rld1_fb_str;
    addr_rld1_bb_str = llm_desc_ptr->addr_rld1_bb_str;

    p0_ena = !!llm_desc_ptr->rld1_bunks;        // NOTE: P0 == RLD1
    p1_ena = !!llm_desc_ptr->rld0_bunks;        // NOTE: P1 == RLD0

    // Massage the code, so that if the user had imbalanced memory per-port (or imbalanced bunks/port), we
    // at least try to configure 'workable' memory.
    if (p0_ena && p1_ena)  // IF BOTH PORTS Enabled (imbalanced memory), select smaller of BOTH
    {
        memport = MIN(llm_desc_ptr->rld0_mbytes, llm_desc_ptr->rld1_mbytes);
        bunkport = MIN(llm_desc_ptr->rld0_bunks, llm_desc_ptr->rld1_bunks);
    }
    else if (p0_ena) // P0=RLD1 Enabled
    {
        memport = llm_desc_ptr->rld1_mbytes;
        bunkport = llm_desc_ptr->rld1_bunks;
    }
    else if (p1_ena) // P1=RLD0 Enabled
    {
        memport = llm_desc_ptr->rld0_mbytes;
        bunkport = llm_desc_ptr->rld0_bunks;
    }
    else
        return -1;

    uint32_t eclk_mhz = llm_desc_ptr->cpu_hz/1000000;



    /* Tweak skew based on cpu clock */
    if (eclk_mhz <= 367)
    {
        tskw_cyc = 0;
    }
    else
    {
        tskw_cyc = 1;
    }

    /* Determine clock divider ratio (only required for CN58XX) */
    if (OCTEON_IS_MODEL(OCTEON_CN58XX))
    {
        uint32_t max_llm_clock_mhz = llm_desc_ptr->max_rld_clock_mhz;
        if (!max_llm_clock_mhz)
        {
            max_llm_clock_mhz = 400;  /* Default to 400 MHz */
            cvmx_dprintf("Warning, using default max_rld_clock_mhz of: %lu MHz\n", (unsigned long)max_llm_clock_mhz);
        }

        /* Compute the divisor, and round up */
        clkdiv = eclk_mhz/max_llm_clock_mhz;
        if (clkdiv * max_llm_clock_mhz < eclk_mhz)
            clkdiv++;

        if (clkdiv > 4)
        {
            cvmx_dprintf("ERROR: CN58XX LLM clock divisor out of range\n");
            goto TERMINATE;
        }
        if (clkdiv < 2)
            clkdiv = 2;

        cvmx_dprintf("Using llm clock divisor: %d, llm clock is: %lu MHz\n", clkdiv, (unsigned long)eclk_mhz/clkdiv);
        /* Translate divisor into bit encoding for register */
        /* 0 -> div 2
        ** 1 -> reserved
        ** 2 -> div 3
        ** 3 -> div 4
        */
        if (clkdiv == 2)
            clkdiv_enc = 0;
        else
            clkdiv_enc = clkdiv - 1;

    /* Odd divisor needs sil_lat to be 2 */
        if (clkdiv == 0x3)
            sil_lat = 2;

        /* Increment tskw for high clock speeds */
        if ((unsigned long)eclk_mhz/clkdiv >= 375)
            tskw_cyc += 1;
    }

    eclk_ps = (1000000+(eclk_mhz-1)) / eclk_mhz;  // round up if nonzero remainder
    //=======================================================================

    //=======================================================================
    // Now, Query User for DFA Memory Type
    if (mtype != 0)
    {
        goto TERMINATE;         // Complete this code for FCRAM usage on N3K-P2
    }
    //=======================================================================
    // Query what the tRC(min) value is from the data sheets
    //=======================================================================
    // Now determine the Best CFG based on Memory clock(ps) and tRCmin(ns)
    mclk_ps = eclk_ps * clkdiv;
    trc_cyc = ((trcmin * 1000)/mclk_ps);
    trc_mod = ((trcmin * 1000) % mclk_ps);
    // If remainder exists, bump up to the next integer multiple
    if (trc_mod != 0)
    {
        trc_cyc = trc_cyc + 1;
    }
    // If tRC is now ODD, then bump it to the next EVEN integer (RLDRAM-II does not support odd tRC values at this time).
    if (trc_cyc & 1)
    {
        trc_cyc = trc_cyc + 1;           // Bump it to an even #
    }
    // RLDRAM CFG Range Check: If the computed trc_cyc is less than 4, then set it to min CFG1 [tRC=4]
    if (trc_cyc < 4)
    {
        trc_cyc = 4;             // If computed trc_cyc < 4 then clamp to 4
    }
    else if (trc_cyc > 8)
    {    // If the computed trc_cyc > 8, then report an error (because RLDRAM cannot support a tRC>8
        goto TERMINATE;
    }
    // Assuming all is ok(up to here)
    // At this point the tRC_cyc has been clamped  between 4 and 8 (and is even), So it can only be 4,6,8 which are
    // the RLDRAM valid CFG range values.
    trl_cyc = trc_cyc;                 // tRL = tRC (for RLDRAM=II)
    twl_cyc = trl_cyc + 1;             // tWL = tRL + 1 (for RLDRAM-II)
    // NOTE: RLDRAM-II (as of 4/25/05) only have 3 supported CFG encodings:
    if (trc_cyc == 4)
    {
        rldcfg = 1;           // CFG #1 (tRL=4/tRC=4/tWL=5)
    }
    else if (trc_cyc == 6)
    {
        rldcfg = 2;           // CFG #2 (tRL=6/tRC=6/tWL=7)
    }
    else if (trc_cyc == 8)
    {
        rldcfg = 3;           // CFG #3 (tRL=8/tRC=8/tWL=9)
    }
    else
    {
        goto TERMINATE;
    }
    //=======================================================================
    mrs_dat = ( (mrs_odt << 9) | (mrs_impmatch << 8) | (mrs_dllrst << 7) | rldcfg );
    //=======================================================================
    // If there is only a single bunk, then skip over address mapping queries (which are not required)
    if (bunkport == 1)
    {
        goto CALC_PBUNK;
    }

    /* Process the address mappings */
    /* Note that that RLD0 pins corresponds to Port#1, and
    **                RLD1 pins corresponds to Port#0.
    */
    mrs_dat_p1bunk0 = process_address_map_str(mrs_dat, addr_rld0_fb_str);
    mrs_dat_p1bunk1 = process_address_map_str(mrs_dat, addr_rld0_bb_str);
    mrs_dat_p0bunk0 = process_address_map_str(mrs_dat, addr_rld1_fb_str);
    mrs_dat_p0bunk1 = process_address_map_str(mrs_dat, addr_rld1_bb_str);


    //=======================================================================
    CALC_PBUNK:
    // Determine the PBUNK field (based on Memory/Bunk)
    // This determines the addr bit used to distinguish when crossing a bunk.
    // NOTE: For RLDRAM, the bunk bit is extracted from 'a' programmably selected high
    // order addr bit. [linear address per-bunk]
    if (bunkport == 2)
    {
        membunk = (memport / 2);
    }
    else
    {
        membunk = memport;
    }
    if (membunk == 16)
    {       // 16MB/bunk MA[19]
        pbunk = 0;
    }
    else if (membunk == 32)
    {  // 32MB/bunk MA[20]
        pbunk = 1;
    }
    else if (membunk == 64)
    {  // 64MB/bunk MA[21]
        pbunk = 2;
    }
    else if (membunk == 128)
    { // 128MB/bunk MA[22]
        pbunk = 3;
    }
    else if (membunk == 256)
    { // 256MB/bunk MA[23]
        pbunk = 4;
    }
    else if (membunk == 512)
    { // 512MB/bunk
    }
    //=======================================================================
    //=======================================================================
    //=======================================================================
    // Now determine N3K REFINT
    trefi_ns = (tref_ms * 1000 * 1000) / (rows * 1024);
    ref512int = ((trefi_ns * 1000) / (eclk_ps * 512));
    ref512mod = ((trefi_ns * 1000) % (eclk_ps * 512));
    //=======================================================================
    // Ask about tSKW
#if 0
    if (tskw_ps ==  0)
    {
        tskw_cyc = 0;
    }
    else
    { // CEILING function
        tskw_cyc = (tskw_ps / eclk_ps);
        tskw_mod = (tskw_ps % eclk_ps);
        if (tskw_mod != 0)
        {  // If there's a remainder - then bump to next (+1)
            tskw_cyc = tskw_cyc + 1;
        }
    }
#endif
    if (tskw_cyc > 3)
    {
        goto TERMINATE;
    }

    tbl = 1;        // BLEN=2 (ALWAYs for RLDRAM)
    //=======================================================================
    // RW_DLY = (ROUND_UP{[[(TRL+TBL)*2 + tSKW + BPRCH] + 1] / 2}) - tWL
    rw_dly = ((((trl_cyc + tbl) * 2 + tskw_cyc + bprch) + 1) / 2);
    if (rw_dly & 1)
    { // If it's ODD then round up
        rw_dly = rw_dly + 1;
    }
    rw_dly = rw_dly - twl_cyc +1 ;
    if (rw_dly < 0)
    { // range check - is it positive
        goto TERMINATE;
    }
    //=======================================================================
    // WR_DLY = (ROUND_UP[[(tWL + tBL)*2 - tSKW + FPRCH] / 2]) - tRL
    wr_dly = (((twl_cyc + tbl) * 2 - tskw_cyc + fprch) / 2);
    if (wr_dly & 1)
    { // If it's ODD then round up
        wr_dly = wr_dly + 1;
    }
    wr_dly = wr_dly - trl_cyc + 1;
    if (wr_dly < 0)
    { // range check - is it positive
        goto TERMINATE;
    }


    dfa_memcfg0_base = 0;
    dfa_memcfg0_base = ( p0_ena |
                         (p1_ena << 1) |
                         (mtype << 3) |
                         (sil_lat << 4) |
                         (rw_dly << 6) |
                         (wr_dly << 10) |
                         (fprch << 14) |
                         (bprch << 16) |
                         (0 << 18) |         // BLEN=0(2-burst for RLDRAM)
                         (pbunk << 19) |
                         (r2r << 22) |       // R2R=1
    			 (clkdiv_enc << 28 )
                       );


    dfa_memcfg1_base = 0;
    dfa_memcfg1_base = ( ref512int |
                         (tskw_cyc << 4) |
                         (trl_cyc << 8) |
                         (twl_cyc << 12) |
                         (trc_cyc << 16) |
                         (tmrsc_cyc << 20)
                       );




    cfg_ptr->dfa_memcfg0_base = dfa_memcfg0_base;
    cfg_ptr->dfa_memcfg1_base = dfa_memcfg1_base;
    cfg_ptr->mrs_dat_p0bunk0 =  mrs_dat_p0bunk0;
    cfg_ptr->mrs_dat_p1bunk0 =  mrs_dat_p1bunk0;
    cfg_ptr->mrs_dat_p0bunk1 =  mrs_dat_p0bunk1;
    cfg_ptr->mrs_dat_p1bunk1 =  mrs_dat_p1bunk1;
    cfg_ptr->p0_ena =           p0_ena;
    cfg_ptr->p1_ena =           p1_ena;
    cfg_ptr->bunkport =         bunkport;
    //=======================================================================

    return(0);
    TERMINATE:
    return(-1);

}