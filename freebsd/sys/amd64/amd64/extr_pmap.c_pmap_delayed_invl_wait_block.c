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
typedef  scalar_t__ u_long ;
struct turnstile {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TS_SHARED_QUEUE ; 
 scalar_t__ atomic_load_long (scalar_t__*) ; 
 int /*<<< orphan*/  invl_gen_ts ; 
 int /*<<< orphan*/  turnstile_cancel (struct turnstile*) ; 
 struct turnstile* turnstile_trywait (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  turnstile_wait (struct turnstile*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
pmap_delayed_invl_wait_block(u_long *m_gen, u_long *invl_gen)
{
	struct turnstile *ts;

	ts = turnstile_trywait(&invl_gen_ts);
	if (*m_gen > atomic_load_long(invl_gen))
		turnstile_wait(ts, NULL, TS_SHARED_QUEUE);
	else
		turnstile_cancel(ts);
}