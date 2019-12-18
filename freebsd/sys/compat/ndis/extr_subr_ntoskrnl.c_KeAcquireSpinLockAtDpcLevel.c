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
typedef  int /*<<< orphan*/  kspin_lock ;

/* Variables and functions */
 scalar_t__ atomic_cmpset_acq_int (int /*<<< orphan*/  volatile*,int /*<<< orphan*/ ,int) ; 

void
KeAcquireSpinLockAtDpcLevel(kspin_lock *lock)
{
	while (atomic_cmpset_acq_int((volatile u_int *)lock, 0, 1) == 0)
		/* sit and spin */;
}