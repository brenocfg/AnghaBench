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
struct syncache_head {int dummy; } ;
struct syncache {int dummy; } ;
struct in_conninfo {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SCH_LOCK_ASSERT (struct syncache_head*) ; 
 int /*<<< orphan*/  SCH_UNLOCK (struct syncache_head*) ; 
 int /*<<< orphan*/  TCPSTAT_INC (int /*<<< orphan*/ ) ; 
 scalar_t__ syncache_cookiesonly () ; 
 int /*<<< orphan*/  syncache_drop (struct syncache*,struct syncache_head*) ; 
 struct syncache* syncache_lookup (struct in_conninfo*,struct syncache_head**) ; 
 int /*<<< orphan*/  tcps_sc_badack ; 

void
syncache_badack(struct in_conninfo *inc)
{
	struct syncache *sc;
	struct syncache_head *sch;

	if (syncache_cookiesonly())
		return;
	sc = syncache_lookup(inc, &sch);	/* returns locked sch */
	SCH_LOCK_ASSERT(sch);
	if (sc != NULL) {
		syncache_drop(sc, sch);
		TCPSTAT_INC(tcps_sc_badack);
	}
	SCH_UNLOCK(sch);
}