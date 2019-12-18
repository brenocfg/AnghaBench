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
struct ioapic_intsrc {int dummy; } ;
struct intsrc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  icu_lock ; 
 int /*<<< orphan*/  ioapic_program_intpin (struct ioapic_intsrc*) ; 
 int /*<<< orphan*/  mtx_lock_spin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock_spin (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ioapic_reprogram_intpin(struct intsrc *isrc)
{

	mtx_lock_spin(&icu_lock);
	ioapic_program_intpin((struct ioapic_intsrc *)isrc);
	mtx_unlock_spin(&icu_lock);
}