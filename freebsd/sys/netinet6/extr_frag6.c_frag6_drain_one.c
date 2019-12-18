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
typedef  scalar_t__ uint32_t ;
struct ip6q {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IP6QB_HEAD (scalar_t__) ; 
 int /*<<< orphan*/  IP6QB_LOCK (scalar_t__) ; 
 int /*<<< orphan*/  IP6QB_UNLOCK (scalar_t__) ; 
 scalar_t__ IP6REASS_NHASH ; 
 int /*<<< orphan*/  IP6STAT_INC (int /*<<< orphan*/ ) ; 
 struct ip6q* TAILQ_FIRST (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  frag6_freef (struct ip6q*,scalar_t__) ; 
 int /*<<< orphan*/  ip6s_fragdropped ; 

__attribute__((used)) static void
frag6_drain_one(void)
{
	struct ip6q *q6;
	uint32_t bucket;

	for (bucket = 0; bucket < IP6REASS_NHASH; bucket++) {
		IP6QB_LOCK(bucket);
		while ((q6 = TAILQ_FIRST(IP6QB_HEAD(bucket))) != NULL) {
			IP6STAT_INC(ip6s_fragdropped);
			/* XXX in6_ifstat_inc(ifp, ifs6_reass_fail) */
			frag6_freef(q6, bucket);
		}
		IP6QB_UNLOCK(bucket);
	}
}