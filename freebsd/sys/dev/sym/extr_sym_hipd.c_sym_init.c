#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
typedef  TYPE_4__* tcb_p ;
typedef  TYPE_5__* hcb_p ;
struct TYPE_18__ {int rv_scntl0; int myaddr; int rv_dmode; int rv_ctest5; int rv_dcntl; int rv_ctest3; int rv_ctest4; int features; int rv_stest2; scalar_t__ device_id; int rv_ccntl0; int rv_ccntl1; int scsi_mode; int ram_ws; int /*<<< orphan*/  path; scalar_t__ hcb_ba; scalar_t__ istat_sem; int /*<<< orphan*/  scripta_sz; int /*<<< orphan*/  scripta0; scalar_t__ scr_ram_seg; int /*<<< orphan*/  scriptb_sz; int /*<<< orphan*/  scriptb0; scalar_t__ ram_ba; int /*<<< orphan*/  rv_scntl3; TYPE_4__* target; int /*<<< orphan*/  (* fw_patch ) (TYPE_5__*) ;scalar_t__ dqueueget; void** dqueue; scalar_t__ dqueue_ba; scalar_t__ squeueput; void** squeue; scalar_t__ idletask_ba; scalar_t__ squeue_ba; } ;
struct TYPE_15__ {scalar_t__ options; int /*<<< orphan*/  width; scalar_t__ offset; scalar_t__ period; } ;
struct TYPE_16__ {TYPE_2__ current; } ;
struct TYPE_14__ {scalar_t__ uval; int /*<<< orphan*/  wval; scalar_t__ sval; } ;
struct TYPE_17__ {TYPE_3__ tinfo; TYPE_1__ head; scalar_t__ to_reset; } ;

/* Variables and functions */
 int /*<<< orphan*/  AC_BUS_RESET ; 
 int BF ; 
 int /*<<< orphan*/  BUS_8_BIT ; 
 int /*<<< orphan*/  CAM_SCSI_BUS_RESET ; 
 int /*<<< orphan*/  CLF ; 
 int CSF ; 
 int DISAIP ; 
 int DPR ; 
 int EXT ; 
 int FE_C10 ; 
 int FE_DAC ; 
 int FE_LED0 ; 
 int FE_LEDC ; 
 int FE_NOPM ; 
 int FE_ULTRA2 ; 
 int FE_ULTRA3 ; 
 unsigned long HTH ; 
 int IID ; 
 int INB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INW (int /*<<< orphan*/ ) ; 
 unsigned long MA ; 
 int MAX_QUEUE ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  MDELAY (int) ; 
 int MDPE ; 
 int NOCOM ; 
 int /*<<< orphan*/  OUTB (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  OUTL (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  OUTL_DSP (scalar_t__) ; 
 int /*<<< orphan*/  OUTONB (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OUTONW (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OUTRAM_OFF (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OUTW (int /*<<< orphan*/ ,unsigned long) ; 
 unsigned long PAR ; 
 scalar_t__ PCI_ID_LSI53C1010 ; 
 scalar_t__ PCI_ID_LSI53C1010_2 ; 
 scalar_t__ PCI_ID_SYM53C875 ; 
 scalar_t__ PCI_ID_SYM53C896 ; 
 int RRE ; 
 unsigned long RST ; 
 int /*<<< orphan*/  SBMC ; 
 scalar_t__ SCRIPTA_BA (TYPE_5__*,int /*<<< orphan*/ ) ; 
 scalar_t__ SCRIPTB_BA (TYPE_5__*,int /*<<< orphan*/ ) ; 
 unsigned long SGE ; 
 int SIGP ; 
 int SIR ; 
 int SMODE ; 
 int SSI ; 
 unsigned long STO ; 
 int SYM_CONF_MAX_TARGET ; 
 int /*<<< orphan*/  SYM_LOCK_ASSERT (int /*<<< orphan*/ ) ; 
 int TE ; 
 unsigned long UDC ; 
 int /*<<< orphan*/  UDELAY (int) ; 
 void* cpu_to_scr (scalar_t__) ; 
 int /*<<< orphan*/  init ; 
 int /*<<< orphan*/  nc_aipcntl1 ; 
 int /*<<< orphan*/  nc_ccntl0 ; 
 int /*<<< orphan*/  nc_ccntl1 ; 
 int /*<<< orphan*/  nc_ctest0 ; 
 int /*<<< orphan*/  nc_ctest3 ; 
 int /*<<< orphan*/  nc_ctest4 ; 
 int /*<<< orphan*/  nc_ctest5 ; 
 int /*<<< orphan*/  nc_dcntl ; 
 int /*<<< orphan*/  nc_dien ; 
 int /*<<< orphan*/  nc_dmode ; 
 int /*<<< orphan*/  nc_dsa ; 
 int /*<<< orphan*/  nc_gpcntl ; 
 int /*<<< orphan*/  nc_istat ; 
 int /*<<< orphan*/  nc_mmrs ; 
 int /*<<< orphan*/  nc_mmws ; 
 int /*<<< orphan*/  nc_pmjad1 ; 
 int /*<<< orphan*/  nc_pmjad2 ; 
 int /*<<< orphan*/  nc_respid ; 
 int /*<<< orphan*/  nc_scid ; 
 int /*<<< orphan*/  nc_scntl0 ; 
 int /*<<< orphan*/  nc_scntl1 ; 
 int /*<<< orphan*/  nc_sfs ; 
 int /*<<< orphan*/  nc_sien ; 
 int /*<<< orphan*/  nc_sist ; 
 int /*<<< orphan*/  nc_stest1 ; 
 int /*<<< orphan*/  nc_stest2 ; 
 int /*<<< orphan*/  nc_stest3 ; 
 int /*<<< orphan*/  nc_stest4 ; 
 int /*<<< orphan*/  nc_stime0 ; 
 int /*<<< orphan*/  pm_handle ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  start64 ; 
 int /*<<< orphan*/  stub1 (TYPE_5__*) ; 
 int /*<<< orphan*/  sym_flush_busy_queue (TYPE_5__*,int /*<<< orphan*/ ) ; 
 char* sym_name (TYPE_5__*) ; 
 int /*<<< orphan*/  sym_selectclock (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sym_soft_reset (TYPE_5__*) ; 
 int sym_verbose ; 
 int /*<<< orphan*/  xpt_async (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void sym_init (hcb_p np, int reason)
{
 	int	i;
	u32	phys;

	SYM_LOCK_ASSERT(MA_OWNED);

 	/*
	 *  Reset chip if asked, otherwise just clear fifos.
 	 */
	if (reason == 1)
		sym_soft_reset(np);
	else {
		OUTB (nc_stest3, TE|CSF);
		OUTONB (nc_ctest3, CLF);
	}

	/*
	 *  Clear Start Queue
	 */
	phys = np->squeue_ba;
	for (i = 0; i < MAX_QUEUE*2; i += 2) {
		np->squeue[i]   = cpu_to_scr(np->idletask_ba);
		np->squeue[i+1] = cpu_to_scr(phys + (i+2)*4);
	}
	np->squeue[MAX_QUEUE*2-1] = cpu_to_scr(phys);

	/*
	 *  Start at first entry.
	 */
	np->squeueput = 0;

	/*
	 *  Clear Done Queue
	 */
	phys = np->dqueue_ba;
	for (i = 0; i < MAX_QUEUE*2; i += 2) {
		np->dqueue[i]   = 0;
		np->dqueue[i+1] = cpu_to_scr(phys + (i+2)*4);
	}
	np->dqueue[MAX_QUEUE*2-1] = cpu_to_scr(phys);

	/*
	 *  Start at first entry.
	 */
	np->dqueueget = 0;

	/*
	 *  Install patches in scripts.
	 *  This also let point to first position the start
	 *  and done queue pointers used from SCRIPTS.
	 */
	np->fw_patch(np);

	/*
	 *  Wakeup all pending jobs.
	 */
	sym_flush_busy_queue(np, CAM_SCSI_BUS_RESET);

	/*
	 *  Init chip.
	 */
	OUTB (nc_istat,  0x00   );	/*  Remove Reset, abort */
	UDELAY (2000);	/* The 895 needs time for the bus mode to settle */

	OUTB (nc_scntl0, np->rv_scntl0 | 0xc0);
					/*  full arb., ena parity, par->ATN  */
	OUTB (nc_scntl1, 0x00);		/*  odd parity, and remove CRST!! */

	sym_selectclock(np, np->rv_scntl3);	/* Select SCSI clock */

	OUTB (nc_scid  , RRE|np->myaddr);	/* Adapter SCSI address */
	OUTW (nc_respid, 1ul<<np->myaddr);	/* Id to respond to */
	OUTB (nc_istat , SIGP	);		/*  Signal Process */
	OUTB (nc_dmode , np->rv_dmode);		/* Burst length, dma mode */
	OUTB (nc_ctest5, np->rv_ctest5);	/* Large fifo + large burst */

	OUTB (nc_dcntl , NOCOM|np->rv_dcntl);	/* Protect SFBR */
	OUTB (nc_ctest3, np->rv_ctest3);	/* Write and invalidate */
	OUTB (nc_ctest4, np->rv_ctest4);	/* Master parity checking */

	/* Extended Sreq/Sack filtering not supported on the C10 */
	if (np->features & FE_C10)
		OUTB (nc_stest2, np->rv_stest2);
	else
		OUTB (nc_stest2, EXT|np->rv_stest2);

	OUTB (nc_stest3, TE);			/* TolerANT enable */
	OUTB (nc_stime0, 0x0c);			/* HTH disabled  STO 0.25 sec */

	/*
	 *  For now, disable AIP generation on C1010-66.
	 */
	if (np->device_id == PCI_ID_LSI53C1010_2)
		OUTB (nc_aipcntl1, DISAIP);

	/*
	 *  C10101 Errata.
	 *  Errant SGE's when in narrow. Write bits 4 & 5 of
	 *  STEST1 register to disable SGE. We probably should do
	 *  that from SCRIPTS for each selection/reselection, but
	 *  I just don't want. :)
	 */
	if (np->device_id == PCI_ID_LSI53C1010 &&
	    /* np->revision_id < 0xff */ 1)
		OUTB (nc_stest1, INB(nc_stest1) | 0x30);

	/*
	 *  DEL 441 - 53C876 Rev 5 - Part Number 609-0392787/2788 - ITEM 2.
	 *  Disable overlapped arbitration for some dual function devices,
	 *  regardless revision id (kind of post-chip-design feature. ;-))
	 */
	if (np->device_id == PCI_ID_SYM53C875)
		OUTB (nc_ctest0, (1<<5));
	else if (np->device_id == PCI_ID_SYM53C896)
		np->rv_ccntl0 |= DPR;

	/*
	 *  Write CCNTL0/CCNTL1 for chips capable of 64 bit addressing
	 *  and/or hardware phase mismatch, since only such chips
	 *  seem to support those IO registers.
	 */
	if (np->features & (FE_DAC|FE_NOPM)) {
		OUTB (nc_ccntl0, np->rv_ccntl0);
		OUTB (nc_ccntl1, np->rv_ccntl1);
	}

	/*
	 *  If phase mismatch handled by scripts (895A/896/1010),
	 *  set PM jump addresses.
	 */
	if (np->features & FE_NOPM) {
		OUTL (nc_pmjad1, SCRIPTB_BA (np, pm_handle));
		OUTL (nc_pmjad2, SCRIPTB_BA (np, pm_handle));
	}

	/*
	 *    Enable GPIO0 pin for writing if LED support from SCRIPTS.
	 *    Also set GPIO5 and clear GPIO6 if hardware LED control.
	 */
	if (np->features & FE_LED0)
		OUTB(nc_gpcntl, INB(nc_gpcntl) & ~0x01);
	else if (np->features & FE_LEDC)
		OUTB(nc_gpcntl, (INB(nc_gpcntl) & ~0x41) | 0x20);

	/*
	 *      enable ints
	 */
	OUTW (nc_sien , STO|HTH|MA|SGE|UDC|RST|PAR);
	OUTB (nc_dien , MDPE|BF|SSI|SIR|IID);

	/*
	 *  For 895/6 enable SBMC interrupt and save current SCSI bus mode.
	 *  Try to eat the spurious SBMC interrupt that may occur when
	 *  we reset the chip but not the SCSI BUS (at initialization).
	 */
	if (np->features & (FE_ULTRA2|FE_ULTRA3)) {
		OUTONW (nc_sien, SBMC);
		if (reason == 0) {
			MDELAY(100);
			INW (nc_sist);
		}
		np->scsi_mode = INB (nc_stest4) & SMODE;
	}

	/*
	 *  Fill in target structure.
	 *  Reinitialize usrsync.
	 *  Reinitialize usrwide.
	 *  Prepare sync negotiation according to actual SCSI bus mode.
	 */
	for (i=0;i<SYM_CONF_MAX_TARGET;i++) {
		tcb_p tp = &np->target[i];

		tp->to_reset  = 0;
		tp->head.sval = 0;
		tp->head.wval = np->rv_scntl3;
		tp->head.uval = 0;

		tp->tinfo.current.period = 0;
		tp->tinfo.current.offset = 0;
		tp->tinfo.current.width  = BUS_8_BIT;
		tp->tinfo.current.options = 0;
	}

	/*
	 *  Download SCSI SCRIPTS to on-chip RAM if present,
	 *  and start script processor.
	 */
	if (np->ram_ba) {
		if (sym_verbose > 1)
			printf ("%s: Downloading SCSI SCRIPTS.\n",
				sym_name(np));
		if (np->ram_ws == 8192) {
			OUTRAM_OFF(4096, np->scriptb0, np->scriptb_sz);
			OUTL (nc_mmws, np->scr_ram_seg);
			OUTL (nc_mmrs, np->scr_ram_seg);
			OUTL (nc_sfs,  np->scr_ram_seg);
			phys = SCRIPTB_BA (np, start64);
		}
		else
			phys = SCRIPTA_BA (np, init);
		OUTRAM_OFF(0, np->scripta0, np->scripta_sz);
	}
	else
		phys = SCRIPTA_BA (np, init);

	np->istat_sem = 0;

	OUTL (nc_dsa, np->hcb_ba);
	OUTL_DSP (phys);

	/*
	 *  Notify the XPT about the RESET condition.
	 */
	if (reason != 0)
		xpt_async(AC_BUS_RESET, np->path, NULL);
}