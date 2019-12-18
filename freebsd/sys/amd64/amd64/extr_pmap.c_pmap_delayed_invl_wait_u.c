#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vm_page_t ;
typedef  scalar_t__ u_long ;
struct lock_delay_arg {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  gen; } ;

/* Variables and functions */
 int /*<<< orphan*/  PV_STAT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_add_int (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  atomic_add_long (int /*<<< orphan*/ *,int) ; 
 scalar_t__ atomic_load_long (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  di_delay ; 
 int /*<<< orphan*/  invl_wait ; 
 int /*<<< orphan*/  invl_wait_slow ; 
 int /*<<< orphan*/  lock_delay (struct lock_delay_arg*) ; 
 int /*<<< orphan*/  lock_delay_arg_init (struct lock_delay_arg*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pmap_delayed_invl_callout_func ; 
 scalar_t__* pmap_delayed_invl_genp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmap_delayed_invl_wait_block (scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pmap_invl_callout ; 
 int /*<<< orphan*/  pmap_invl_callout_inited ; 
 TYPE_1__ pmap_invl_gen_head ; 
 int /*<<< orphan*/  pmap_invl_waiters ; 

__attribute__((used)) static void
pmap_delayed_invl_wait_u(vm_page_t m)
{
	u_long *m_gen;
	struct lock_delay_arg lda;
	bool fast;

	fast = true;
	m_gen = pmap_delayed_invl_genp(m);
	lock_delay_arg_init(&lda, &di_delay);
	while (*m_gen > atomic_load_long(&pmap_invl_gen_head.gen)) {
		if (fast || !pmap_invl_callout_inited) {
			PV_STAT(atomic_add_long(&invl_wait, 1));
			lock_delay(&lda);
			fast = false;
		} else {
			/*
			 * The page's invalidation generation number
			 * is still below the current thread's number.
			 * Prepare to block so that we do not waste
			 * CPU cycles or worse, suffer livelock.
			 *
			 * Since it is impossible to block without
			 * racing with pmap_delayed_invl_finish_u(),
			 * prepare for the race by incrementing
			 * pmap_invl_waiters and arming a 1-tick
			 * callout which will unblock us if we lose
			 * the race.
			 */
			atomic_add_int(&pmap_invl_waiters, 1);

			/*
			 * Re-check the current thread's invalidation
			 * generation after incrementing
			 * pmap_invl_waiters, so that there is no race
			 * with pmap_delayed_invl_finish_u() setting
			 * the page generation and checking
			 * pmap_invl_waiters.  The only race allowed
			 * is for a missed unblock, which is handled
			 * by the callout.
			 */
			if (*m_gen >
			    atomic_load_long(&pmap_invl_gen_head.gen)) {
				callout_reset(&pmap_invl_callout, 1,
				    pmap_delayed_invl_callout_func, NULL);
				PV_STAT(atomic_add_long(&invl_wait_slow, 1));
				pmap_delayed_invl_wait_block(m_gen,
				    &pmap_invl_gen_head.gen);
			}
			atomic_add_int(&pmap_invl_waiters, -1);
		}
	}
}