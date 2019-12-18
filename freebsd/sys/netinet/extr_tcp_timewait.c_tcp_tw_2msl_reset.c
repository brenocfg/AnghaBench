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
struct tcptw {scalar_t__ tw_time; int /*<<< orphan*/  tw_inpcb; } ;

/* Variables and functions */
 int /*<<< orphan*/  INP_WLOCK_ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NET_EPOCH_ASSERT () ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct tcptw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct tcptw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TW_WLOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TW_WUNLOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  V_tw_lock ; 
 int /*<<< orphan*/  V_twq_2msl ; 
 int tcp_msl ; 
 scalar_t__ ticks ; 
 int /*<<< orphan*/  tw_2msl ; 

__attribute__((used)) static void
tcp_tw_2msl_reset(struct tcptw *tw, int rearm)
{

	NET_EPOCH_ASSERT();
	INP_WLOCK_ASSERT(tw->tw_inpcb);

	TW_WLOCK(V_tw_lock);
	if (rearm)
		TAILQ_REMOVE(&V_twq_2msl, tw, tw_2msl);
	tw->tw_time = ticks + 2 * tcp_msl;
	TAILQ_INSERT_TAIL(&V_twq_2msl, tw, tw_2msl);
	TW_WUNLOCK(V_tw_lock);
}