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
struct sfxge_evq {scalar_t__ init_state; } ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  SFXGE_EVQ_LOCK_ASSERT_OWNED (struct sfxge_evq*) ; 
 scalar_t__ SFXGE_EVQ_STARTED ; 
 scalar_t__ SFXGE_EVQ_STARTING ; 

__attribute__((used)) static boolean_t
sfxge_ev_initialized(void *arg)
{
	struct sfxge_evq *evq;

	evq = (struct sfxge_evq *)arg;
	SFXGE_EVQ_LOCK_ASSERT_OWNED(evq);

	/* Init done events may be duplicated on 7xxx */
	KASSERT(evq->init_state == SFXGE_EVQ_STARTING ||
		evq->init_state == SFXGE_EVQ_STARTED,
	    ("evq not starting"));

	evq->init_state = SFXGE_EVQ_STARTED;

	return (0);
}