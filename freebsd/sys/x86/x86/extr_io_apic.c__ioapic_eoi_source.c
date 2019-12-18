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
struct ioapic_intsrc {int io_vector; int io_lowreg; int /*<<< orphan*/  io_intpin; scalar_t__ io_edgetrigger; } ;
struct ioapic {scalar_t__ io_addr; scalar_t__ io_haseoi; } ;
struct intsrc {scalar_t__ is_pic; } ;

/* Variables and functions */
 int IOAPIC_EOIR ; 
 int /*<<< orphan*/  IOAPIC_REDTBL_LO (int /*<<< orphan*/ ) ; 
 int IOART_INTMSET ; 
 int IOART_TRGREDG ; 
 int IOART_TRGRLVL ; 
 int /*<<< orphan*/  icu_lock ; 
 int /*<<< orphan*/  ioapic_write (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  lapic_eoi () ; 
 int /*<<< orphan*/  lapic_eoi_suppression ; 
 int /*<<< orphan*/  mtx_lock_spin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock_spin (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
_ioapic_eoi_source(struct intsrc *isrc, int locked)
{
	struct ioapic_intsrc *src;
	struct ioapic *io;
	volatile uint32_t *apic_eoi;
	uint32_t low1;

	lapic_eoi();
	if (!lapic_eoi_suppression)
		return;
	src = (struct ioapic_intsrc *)isrc;
	if (src->io_edgetrigger)
		return;
	io = (struct ioapic *)isrc->is_pic;

	/*
	 * Handle targeted EOI for level-triggered pins, if broadcast
	 * EOI suppression is supported by LAPICs.
	 */
	if (io->io_haseoi) {
		/*
		 * If IOAPIC has EOI Register, simply write vector
		 * number into the reg.
		 */
		apic_eoi = (volatile uint32_t *)((volatile char *)
		    io->io_addr + IOAPIC_EOIR);
		*apic_eoi = src->io_vector;
	} else {
		/*
		 * Otherwise, if IO-APIC is too old to provide EOIR,
		 * do what Intel did for the Linux kernel. Temporary
		 * switch the pin to edge-trigger and back, masking
		 * the pin during the trick.
		 */
		if (!locked)
			mtx_lock_spin(&icu_lock);
		low1 = src->io_lowreg;
		low1 &= ~IOART_TRGRLVL;
		low1 |= IOART_TRGREDG | IOART_INTMSET;
		ioapic_write(io->io_addr, IOAPIC_REDTBL_LO(src->io_intpin),
		    low1);
		ioapic_write(io->io_addr, IOAPIC_REDTBL_LO(src->io_intpin),
		    src->io_lowreg);
		if (!locked)
			mtx_unlock_spin(&icu_lock);
	}
}