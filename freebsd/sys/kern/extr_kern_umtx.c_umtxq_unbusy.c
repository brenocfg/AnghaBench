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
struct umtxq_chain {scalar_t__ uc_busy; scalar_t__ uc_waiters; int /*<<< orphan*/  uc_lock; } ;
struct umtx_key {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct umtxq_chain* umtxq_getchain (struct umtx_key*) ; 
 int /*<<< orphan*/  wakeup_one (struct umtxq_chain*) ; 

__attribute__((used)) static inline void
umtxq_unbusy(struct umtx_key *key)
{
	struct umtxq_chain *uc;

	uc = umtxq_getchain(key);
	mtx_assert(&uc->uc_lock, MA_OWNED);
	KASSERT(uc->uc_busy != 0, ("not busy"));
	uc->uc_busy = 0;
	if (uc->uc_waiters)
		wakeup_one(uc);
}