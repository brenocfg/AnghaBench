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
 int /*<<< orphan*/  atomic_store_rel_int (int /*<<< orphan*/  volatile*,int /*<<< orphan*/ ) ; 

void
KeReleaseSpinLockFromDpcLevel(kspin_lock *lock)
{
	atomic_store_rel_int((volatile u_int *)lock, 0);
}