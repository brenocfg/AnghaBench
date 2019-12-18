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
struct umtx_q {int /*<<< orphan*/  uq_pi_contested; } ;
struct umtx_pi {struct thread* pi_owner; } ;
struct thread {struct umtx_q* td_umtxq; } ;

/* Variables and functions */
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  MPASS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct umtx_pi*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pi_link ; 
 int /*<<< orphan*/  umtx_lock ; 

__attribute__((used)) static void
umtx_pi_setowner(struct umtx_pi *pi, struct thread *owner)
{
	struct umtx_q *uq_owner;

	uq_owner = owner->td_umtxq;
	mtx_assert(&umtx_lock, MA_OWNED);
	MPASS(pi->pi_owner == NULL);
	pi->pi_owner = owner;
	TAILQ_INSERT_TAIL(&uq_owner->uq_pi_contested, pi, pi_link);
}