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
 int /*<<< orphan*/  invl_gen_ts ; 
 scalar_t__ pmap_invl_gen ; 
 int /*<<< orphan*/  turnstile_broadcast (struct turnstile*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  turnstile_chain_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  turnstile_chain_unlock (int /*<<< orphan*/ *) ; 
 struct turnstile* turnstile_lookup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  turnstile_unpend (struct turnstile*) ; 

__attribute__((used)) static void
pmap_delayed_invl_finish_unblock(u_long new_gen)
{
	struct turnstile *ts;

	turnstile_chain_lock(&invl_gen_ts);
	ts = turnstile_lookup(&invl_gen_ts);
	if (new_gen != 0)
		pmap_invl_gen = new_gen;
	if (ts != NULL) {
		turnstile_broadcast(ts, TS_SHARED_QUEUE);
		turnstile_unpend(ts);
	}
	turnstile_chain_unlock(&invl_gen_ts);
}