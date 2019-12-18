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

/* Variables and functions */
 int ACPI_GLOCK_OWNED ; 
 int ACPI_GLOCK_PENDING ; 
 scalar_t__ atomic_cmpset_32 (int volatile*,int,int) ; 

int
acpi_release_global_lock(volatile uint32_t *lock)
{
	uint32_t	new, old;

	do {
		old = *lock;
		new = old & ~(ACPI_GLOCK_PENDING | ACPI_GLOCK_OWNED);
	} while (atomic_cmpset_32(lock, old, new) == 0);

	return ((old & ACPI_GLOCK_PENDING) != 0);
}