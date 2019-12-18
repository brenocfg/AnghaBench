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
struct toedev {int /*<<< orphan*/  (* tod_syncache_added ) (struct toedev*,int /*<<< orphan*/ ) ;} ;
struct syncache_head {int sch_length; scalar_t__ sch_nextc; int /*<<< orphan*/  sch_bucket; int /*<<< orphan*/  sch_last_overflow; } ;
struct syncache {int /*<<< orphan*/  sc_todctx; struct toedev* sc_tod; int /*<<< orphan*/  sc_inc; } ;
struct TYPE_2__ {int bucket_limit; } ;

/* Variables and functions */
 scalar_t__ ADDED_BY_TOE (struct syncache*) ; 
 scalar_t__ INT_MAX ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  SCH_LOCK (struct syncache_head*) ; 
 int /*<<< orphan*/  SCH_UNLOCK (struct syncache_head*) ; 
 int /*<<< orphan*/  TAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_INSERT_HEAD (int /*<<< orphan*/ *,struct syncache*,int /*<<< orphan*/ ) ; 
 struct syncache* TAILQ_LAST (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TCPSTATES_INC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TCPSTAT_INC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TCPS_SYN_RECEIVED ; 
 TYPE_1__ V_tcp_syncache ; 
 int /*<<< orphan*/  sc_hash ; 
 int /*<<< orphan*/  sch_head ; 
 int /*<<< orphan*/  stub1 (struct toedev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  syncache_drop (struct syncache*,struct syncache_head*) ; 
 int /*<<< orphan*/  syncache_pause (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  syncache_timeout (struct syncache*,struct syncache_head*,int) ; 
 int /*<<< orphan*/  tcps_sc_added ; 
 scalar_t__ ticks ; 
 int /*<<< orphan*/  time_uptime ; 

__attribute__((used)) static void
syncache_insert(struct syncache *sc, struct syncache_head *sch)
{
	struct syncache *sc2;

	SCH_LOCK(sch);

	/*
	 * Make sure that we don't overflow the per-bucket limit.
	 * If the bucket is full, toss the oldest element.
	 */
	if (sch->sch_length >= V_tcp_syncache.bucket_limit) {
		KASSERT(!TAILQ_EMPTY(&sch->sch_bucket),
			("sch->sch_length incorrect"));
		syncache_pause(&sc->sc_inc);
		sc2 = TAILQ_LAST(&sch->sch_bucket, sch_head);
		sch->sch_last_overflow = time_uptime;
		syncache_drop(sc2, sch);
	}

	/* Put it into the bucket. */
	TAILQ_INSERT_HEAD(&sch->sch_bucket, sc, sc_hash);
	sch->sch_length++;

#ifdef TCP_OFFLOAD
	if (ADDED_BY_TOE(sc)) {
		struct toedev *tod = sc->sc_tod;

		tod->tod_syncache_added(tod, sc->sc_todctx);
	}
#endif

	/* Reinitialize the bucket row's timer. */
	if (sch->sch_length == 1)
		sch->sch_nextc = ticks + INT_MAX;
	syncache_timeout(sc, sch, 1);

	SCH_UNLOCK(sch);

	TCPSTATES_INC(TCPS_SYN_RECEIVED);
	TCPSTAT_INC(tcps_sc_added);
}