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
typedef  scalar_t__ u_int ;
struct ioapic_intsrc {scalar_t__ io_vector; int io_masked; int /*<<< orphan*/  io_irq; int /*<<< orphan*/  io_cpu; } ;
struct intsrc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  apic_disable_vector (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  apic_free_vector (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  icu_lock ; 
 int /*<<< orphan*/  ioapic_program_intpin (struct ioapic_intsrc*) ; 
 int /*<<< orphan*/  mtx_lock_spin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock_spin (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ioapic_disable_intr(struct intsrc *isrc)
{
	struct ioapic_intsrc *intpin = (struct ioapic_intsrc *)isrc;
	u_int vector;

	if (intpin->io_vector != 0) {
		/* Mask this interrupt pin and free its APIC vector. */
		vector = intpin->io_vector;
		apic_disable_vector(intpin->io_cpu, vector);
		mtx_lock_spin(&icu_lock);
		intpin->io_masked = 1;
		intpin->io_vector = 0;
		ioapic_program_intpin(intpin);
		mtx_unlock_spin(&icu_lock);
		apic_free_vector(intpin->io_cpu, vector, intpin->io_irq);
	}
}