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
typedef  int /*<<< orphan*/  tcp_seq ;
struct syncache_head {int dummy; } ;
struct syncache {scalar_t__ sc_iss; int sc_flags; int sc_rxmits; } ;
struct in_conninfo {int dummy; } ;

/* Variables and functions */
 int SCF_UNREACH ; 
 int /*<<< orphan*/  SCH_LOCK_ASSERT (struct syncache_head*) ; 
 int /*<<< orphan*/  SCH_UNLOCK (struct syncache_head*) ; 
 int /*<<< orphan*/  TCPSTAT_INC (int /*<<< orphan*/ ) ; 
 scalar_t__ ntohl (int /*<<< orphan*/ ) ; 
 scalar_t__ syncache_cookiesonly () ; 
 int /*<<< orphan*/  syncache_drop (struct syncache*,struct syncache_head*) ; 
 struct syncache* syncache_lookup (struct in_conninfo*,struct syncache_head**) ; 
 int /*<<< orphan*/  tcps_sc_unreach ; 

void
syncache_unreach(struct in_conninfo *inc, tcp_seq th_seq)
{
	struct syncache *sc;
	struct syncache_head *sch;

	if (syncache_cookiesonly())
		return;
	sc = syncache_lookup(inc, &sch);	/* returns locked sch */
	SCH_LOCK_ASSERT(sch);
	if (sc == NULL)
		goto done;

	/* If the sequence number != sc_iss, then it's a bogus ICMP msg */
	if (ntohl(th_seq) != sc->sc_iss)
		goto done;

	/*
	 * If we've rertransmitted 3 times and this is our second error,
	 * we remove the entry.  Otherwise, we allow it to continue on.
	 * This prevents us from incorrectly nuking an entry during a
	 * spurious network outage.
	 *
	 * See tcp_notify().
	 */
	if ((sc->sc_flags & SCF_UNREACH) == 0 || sc->sc_rxmits < 3 + 1) {
		sc->sc_flags |= SCF_UNREACH;
		goto done;
	}
	syncache_drop(sc, sch);
	TCPSTAT_INC(tcps_sc_unreach);
done:
	SCH_UNLOCK(sch);
}