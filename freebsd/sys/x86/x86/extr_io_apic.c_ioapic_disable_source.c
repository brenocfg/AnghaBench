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
struct ioapic_intsrc {int io_masked; int io_lowreg; int /*<<< orphan*/  io_intpin; int /*<<< orphan*/  io_edgetrigger; } ;
struct ioapic {int /*<<< orphan*/  io_addr; } ;
struct intsrc {scalar_t__ is_pic; } ;

/* Variables and functions */
 int /*<<< orphan*/  IOAPIC_REDTBL_LO (int /*<<< orphan*/ ) ; 
 int IOART_INTMSET ; 
 int PIC_EOI ; 
 int /*<<< orphan*/  _ioapic_eoi_source (struct intsrc*,int) ; 
 int /*<<< orphan*/  icu_lock ; 
 int /*<<< orphan*/  ioapic_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mtx_lock_spin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock_spin (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ioapic_disable_source(struct intsrc *isrc, int eoi)
{
	struct ioapic_intsrc *intpin = (struct ioapic_intsrc *)isrc;
	struct ioapic *io = (struct ioapic *)isrc->is_pic;
	uint32_t flags;

	mtx_lock_spin(&icu_lock);
	if (!intpin->io_masked && !intpin->io_edgetrigger) {
		flags = intpin->io_lowreg | IOART_INTMSET;
		ioapic_write(io->io_addr, IOAPIC_REDTBL_LO(intpin->io_intpin),
		    flags);
		intpin->io_masked = 1;
	}

	if (eoi == PIC_EOI)
		_ioapic_eoi_source(isrc, 1);

	mtx_unlock_spin(&icu_lock);
}