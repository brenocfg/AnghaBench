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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  kspin_lock ;

/* Variables and functions */
 int /*<<< orphan*/  KeLowerIrql (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KeReleaseSpinLockFromDpcLevel (int /*<<< orphan*/ *) ; 

void
KfReleaseSpinLock(kspin_lock *lock, uint8_t newirql)
{
	KeReleaseSpinLockFromDpcLevel(lock);
	KeLowerIrql(newirql);
}