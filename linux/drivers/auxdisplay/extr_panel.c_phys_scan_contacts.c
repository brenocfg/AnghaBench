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
typedef  int __u64 ;

/* Variables and functions */
 int BIT (int) ; 
 char PNL_PINPUT (int /*<<< orphan*/ ) ; 
 int phys_curr ; 
 int phys_prev ; 
 int phys_read ; 
 int phys_read_prev ; 
 int /*<<< orphan*/  pprt ; 
 char r_dtr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_str (int /*<<< orphan*/ ) ; 
 char scan_mask_i ; 
 char scan_mask_o ; 
 int /*<<< orphan*/  w_dtr (int /*<<< orphan*/ ,char) ; 

__attribute__((used)) static void phys_scan_contacts(void)
{
	int bit, bitval;
	char oldval;
	char bitmask;
	char gndmask;

	phys_prev = phys_curr;
	phys_read_prev = phys_read;
	phys_read = 0;		/* flush all signals */

	/* keep track of old value, with all outputs disabled */
	oldval = r_dtr(pprt) | scan_mask_o;
	/* activate all keyboard outputs (active low) */
	w_dtr(pprt, oldval & ~scan_mask_o);

	/* will have a 1 for each bit set to gnd */
	bitmask = PNL_PINPUT(r_str(pprt)) & scan_mask_i;
	/* disable all matrix signals */
	w_dtr(pprt, oldval);

	/* now that all outputs are cleared, the only active input bits are
	 * directly connected to the ground
	 */

	/* 1 for each grounded input */
	gndmask = PNL_PINPUT(r_str(pprt)) & scan_mask_i;

	/* grounded inputs are signals 40-44 */
	phys_read |= (__u64)gndmask << 40;

	if (bitmask != gndmask) {
		/*
		 * since clearing the outputs changed some inputs, we know
		 * that some input signals are currently tied to some outputs.
		 * So we'll scan them.
		 */
		for (bit = 0; bit < 8; bit++) {
			bitval = BIT(bit);

			if (!(scan_mask_o & bitval))	/* skip unused bits */
				continue;

			w_dtr(pprt, oldval & ~bitval);	/* enable this output */
			bitmask = PNL_PINPUT(r_str(pprt)) & ~gndmask;
			phys_read |= (__u64)bitmask << (5 * bit);
		}
		w_dtr(pprt, oldval);	/* disable all outputs */
	}
	/*
	 * this is easy: use old bits when they are flapping,
	 * use new ones when stable
	 */
	phys_curr = (phys_prev & (phys_read ^ phys_read_prev)) |
		    (phys_read & ~(phys_read ^ phys_read_prev));
}