#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  kspin_lock ;
struct TYPE_4__ {int /*<<< orphan*/  ki_list; int /*<<< orphan*/ * ki_lock; int /*<<< orphan*/  ki_lock_priv; void* ki_svcctx; void* ki_svcfunc; } ;
typedef  TYPE_1__ kinterrupt ;

/* Variables and functions */
 TYPE_1__* ExAllocatePoolWithTag (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InsertHeadList (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  KeAcquireSpinLock (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  KeInitializeSpinLock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  KeReleaseSpinLock (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NonPagedPool ; 
 int /*<<< orphan*/  STATUS_INSUFFICIENT_RESOURCES ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int /*<<< orphan*/  ntoskrnl_intlist ; 
 int /*<<< orphan*/  ntoskrnl_intlock ; 

uint32_t
IoConnectInterrupt(kinterrupt **iobj, void *svcfunc, void *svcctx,
	kspin_lock *lock, uint32_t vector, uint8_t irql, uint8_t syncirql,
	uint8_t imode, uint8_t shared, uint32_t affinity, uint8_t savefloat)
{
	uint8_t			curirql;

	*iobj = ExAllocatePoolWithTag(NonPagedPool, sizeof(kinterrupt), 0);
	if (*iobj == NULL)
		return (STATUS_INSUFFICIENT_RESOURCES);

	(*iobj)->ki_svcfunc = svcfunc;
	(*iobj)->ki_svcctx = svcctx;

	if (lock == NULL) {
		KeInitializeSpinLock(&(*iobj)->ki_lock_priv);
		(*iobj)->ki_lock = &(*iobj)->ki_lock_priv;
	} else
		(*iobj)->ki_lock = lock;

	KeAcquireSpinLock(&ntoskrnl_intlock, &curirql);
	InsertHeadList((&ntoskrnl_intlist), (&(*iobj)->ki_list));
	KeReleaseSpinLock(&ntoskrnl_intlock, curirql);

	return (STATUS_SUCCESS);
}