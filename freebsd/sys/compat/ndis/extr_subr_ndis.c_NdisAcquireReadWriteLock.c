#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
struct TYPE_5__ {int /*<<< orphan*/ * nrl_rsvd; int /*<<< orphan*/  nrl_spinlock; } ;
typedef  TYPE_1__ ndis_rw_lock ;
struct TYPE_6__ {int /*<<< orphan*/  nls_oldirql; } ;
typedef  TYPE_2__ ndis_lock_state ;

/* Variables and functions */
 int /*<<< orphan*/  KeAcquireSpinLock (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ TRUE ; 

__attribute__((used)) static void
NdisAcquireReadWriteLock(ndis_rw_lock *lock, uint8_t writeacc,
    ndis_lock_state *state)
{
	if (writeacc == TRUE) {
		KeAcquireSpinLock(&lock->nrl_spinlock, &state->nls_oldirql);
		lock->nrl_rsvd[0]++;
	} else
		lock->nrl_rsvd[1]++;
}