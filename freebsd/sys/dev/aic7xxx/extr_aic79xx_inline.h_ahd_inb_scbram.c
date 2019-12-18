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
typedef  int /*<<< orphan*/  u_int ;
struct ahd_softc {int bugs; } ;

/* Variables and functions */
 int AHD_PCIX_SCBRAM_RD_BUG ; 
 int /*<<< orphan*/  MODE_PTR ; 
 int /*<<< orphan*/  ahd_inb (struct ahd_softc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static __inline u_int
ahd_inb_scbram(struct ahd_softc *ahd, u_int offset)
{
	u_int value;

	/*
	 * Workaround PCI-X Rev A. hardware bug.
	 * After a host read of SCB memory, the chip
	 * may become confused into thinking prefetch
	 * was required.  This starts the discard timer
	 * running and can cause an unexpected discard
	 * timer interrupt.  The work around is to read
	 * a normal register prior to the exhaustion of
	 * the discard timer.  The mode pointer register
	 * has no side effects and so serves well for
	 * this purpose.
	 *
	 * Razor #528
	 */
	value = ahd_inb(ahd, offset);
	if ((ahd->bugs & AHD_PCIX_SCBRAM_RD_BUG) != 0)
		ahd_inb(ahd, MODE_PTR);
	return (value);
}