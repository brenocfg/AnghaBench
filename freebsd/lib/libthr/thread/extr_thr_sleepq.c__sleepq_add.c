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
struct sleepqueue_chain {int sc_enqcnt; int /*<<< orphan*/  sc_queues; } ;
struct sleepqueue {int /*<<< orphan*/  sq_blocked; void* sq_wchan; int /*<<< orphan*/  sq_freeq; } ;
struct pthread {void* wchan; struct sleepqueue* sleepqueue; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_INSERT_HEAD (int /*<<< orphan*/ *,struct sleepqueue*,int /*<<< orphan*/ ) ; 
 struct sleepqueue_chain* SC_LOOKUP (void*) ; 
 int /*<<< orphan*/  SLIST_INSERT_HEAD (int /*<<< orphan*/ *,struct sleepqueue*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAILQ_INSERT_HEAD (int /*<<< orphan*/ *,struct pthread*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct pthread*,int /*<<< orphan*/ ) ; 
 int _thr_queuefifo ; 
 struct sleepqueue* lookup (struct sleepqueue_chain*,void*) ; 
 int /*<<< orphan*/  sq_flink ; 
 int /*<<< orphan*/  sq_hash ; 
 int /*<<< orphan*/  wle ; 

void
_sleepq_add(void *wchan, struct pthread *td)
{
	struct sleepqueue_chain *sc;
	struct sleepqueue *sq;

	sc = SC_LOOKUP(wchan);
	sq = lookup(sc, wchan);
	if (sq != NULL) {
		SLIST_INSERT_HEAD(&sq->sq_freeq, td->sleepqueue, sq_flink);
	} else {
		sq = td->sleepqueue;
		LIST_INSERT_HEAD(&sc->sc_queues, sq, sq_hash);
		sq->sq_wchan = wchan;
		/* sq->sq_type = type; */
	}
	td->sleepqueue = NULL;
	td->wchan = wchan;
	if (((++sc->sc_enqcnt << _thr_queuefifo) & 0xff) != 0)
		TAILQ_INSERT_HEAD(&sq->sq_blocked, td, wle);
	else
		TAILQ_INSERT_TAIL(&sq->sq_blocked, td, wle);
}