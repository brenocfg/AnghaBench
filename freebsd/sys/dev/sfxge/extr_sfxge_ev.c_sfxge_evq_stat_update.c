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
struct sfxge_evq {scalar_t__ init_state; int /*<<< orphan*/  stats; int /*<<< orphan*/  common; scalar_t__ stats_update_time; } ;
typedef  scalar_t__ clock_t ;

/* Variables and functions */
 int /*<<< orphan*/  SFXGE_EVQ_LOCK (struct sfxge_evq*) ; 
 scalar_t__ SFXGE_EVQ_STARTED ; 
 int /*<<< orphan*/  SFXGE_EVQ_UNLOCK (struct sfxge_evq*) ; 
 scalar_t__ __predict_false (int) ; 
 int /*<<< orphan*/  efx_ev_qstats_update (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ hz ; 
 scalar_t__ ticks ; 

__attribute__((used)) static void
sfxge_evq_stat_update(struct sfxge_evq *evq)
{
	clock_t now;

	SFXGE_EVQ_LOCK(evq);

	if (__predict_false(evq->init_state != SFXGE_EVQ_STARTED))
		goto out;

	now = ticks;
	if ((unsigned int)(now - evq->stats_update_time) < (unsigned int)hz)
		goto out;

	evq->stats_update_time = now;
	efx_ev_qstats_update(evq->common, evq->stats);

out:
	SFXGE_EVQ_UNLOCK(evq);
}