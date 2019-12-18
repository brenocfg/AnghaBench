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
typedef  int /*<<< orphan*/  hcb_p ;

/* Variables and functions */
 int GEN ; 
 int INW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OUTB (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  OUTW (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UDELAY (int) ; 
 int /*<<< orphan*/  nc_dien ; 
 int /*<<< orphan*/  nc_scntl3 ; 
 int /*<<< orphan*/  nc_sien ; 
 int /*<<< orphan*/  nc_sist ; 
 int /*<<< orphan*/  nc_stime1 ; 
 int /*<<< orphan*/  printf (char*,char*,int,unsigned int,unsigned int) ; 
 char* sym_name (int /*<<< orphan*/ ) ; 
 int sym_verbose ; 

__attribute__((used)) static unsigned getfreq (hcb_p np, int gen)
{
	unsigned int ms = 0;
	unsigned int f;

	/*
	 * Measure GEN timer delay in order
	 * to calculate SCSI clock frequency
	 *
	 * This code will never execute too
	 * many loop iterations (if DELAY is
	 * reasonably correct). It could get
	 * too low a delay (too high a freq.)
	 * if the CPU is slow executing the
	 * loop for some reason (an NMI, for
	 * example). For this reason we will
	 * if multiple measurements are to be
	 * performed trust the higher delay
	 * (lower frequency returned).
	 */
	OUTW (nc_sien , 0);	/* mask all scsi interrupts */
	(void) INW (nc_sist);	/* clear pending scsi interrupt */
	OUTB (nc_dien , 0);	/* mask all dma interrupts */
	(void) INW (nc_sist);	/* another one, just to be sure :) */
	OUTB (nc_scntl3, 4);	/* set pre-scaler to divide by 3 */
	OUTB (nc_stime1, 0);	/* disable general purpose timer */
	OUTB (nc_stime1, gen);	/* set to nominal delay of 1<<gen * 125us */
	while (!(INW(nc_sist) & GEN) && ms++ < 100000)
		UDELAY (1000);	/* count ms */
	OUTB (nc_stime1, 0);	/* disable general purpose timer */
 	/*
 	 * set prescaler to divide by whatever 0 means
 	 * 0 ought to choose divide by 2, but appears
 	 * to set divide by 3.5 mode in my 53c810 ...
 	 */
 	OUTB (nc_scntl3, 0);

  	/*
 	 * adjust for prescaler, and convert into KHz
  	 */
	f = ms ? ((1 << gen) * 4340) / ms : 0;

	if (sym_verbose >= 2)
		printf ("%s: Delay (GEN=%d): %u msec, %u KHz\n",
			sym_name(np), gen, ms, f);

	return f;
}