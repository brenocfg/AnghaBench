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
struct pic {int dummy; } ;
struct ioapic {int io_numintr; int /*<<< orphan*/ * io_pins; } ;

/* Variables and functions */
 int /*<<< orphan*/  icu_lock ; 
 int /*<<< orphan*/  ioapic_program_intpin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_lock_spin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock_spin (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ioapic_resume(struct pic *pic, bool suspend_cancelled)
{
	struct ioapic *io = (struct ioapic *)pic;
	int i;

	mtx_lock_spin(&icu_lock);
	for (i = 0; i < io->io_numintr; i++)
		ioapic_program_intpin(&io->io_pins[i]);
	mtx_unlock_spin(&icu_lock);
}