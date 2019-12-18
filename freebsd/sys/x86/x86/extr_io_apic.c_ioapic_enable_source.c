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
struct ioapic_intsrc {int io_lowreg; scalar_t__ io_masked; int /*<<< orphan*/  io_intpin; } ;
struct ioapic {int /*<<< orphan*/  io_addr; } ;
struct intsrc {scalar_t__ is_pic; } ;

/* Variables and functions */
 int /*<<< orphan*/  IOAPIC_REDTBL_LO (int /*<<< orphan*/ ) ; 
 int IOART_INTMASK ; 
 int /*<<< orphan*/  icu_lock ; 
 int /*<<< orphan*/  ioapic_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mtx_lock_spin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock_spin (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ioapic_enable_source(struct intsrc *isrc)
{
	struct ioapic_intsrc *intpin = (struct ioapic_intsrc *)isrc;
	struct ioapic *io = (struct ioapic *)isrc->is_pic;
	uint32_t flags;

	mtx_lock_spin(&icu_lock);
	if (intpin->io_masked) {
		flags = intpin->io_lowreg & ~IOART_INTMASK;
		ioapic_write(io->io_addr, IOAPIC_REDTBL_LO(intpin->io_intpin),
		    flags);
		intpin->io_masked = 0;
	}
	mtx_unlock_spin(&icu_lock);
}