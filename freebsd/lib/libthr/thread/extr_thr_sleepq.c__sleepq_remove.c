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
struct sleepqueue {int /*<<< orphan*/  sq_freeq; int /*<<< orphan*/  sq_blocked; } ;
struct pthread {int /*<<< orphan*/ * wchan; struct sleepqueue* sleepqueue; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_REMOVE (struct sleepqueue*,int /*<<< orphan*/ ) ; 
 struct sleepqueue* SLIST_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SLIST_REMOVE_HEAD (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ TAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct pthread*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sq_flink ; 
 int /*<<< orphan*/  sq_hash ; 
 int /*<<< orphan*/  wle ; 

int
_sleepq_remove(struct sleepqueue *sq, struct pthread *td)
{
	int rc;

	TAILQ_REMOVE(&sq->sq_blocked, td, wle);
	if (TAILQ_EMPTY(&sq->sq_blocked)) {
		LIST_REMOVE(sq, sq_hash);
		td->sleepqueue = sq;
		rc = 0;
	} else {
		td->sleepqueue = SLIST_FIRST(&sq->sq_freeq);
		SLIST_REMOVE_HEAD(&sq->sq_freeq, sq_flink);
		rc = 1;
	}
	td->wchan = NULL;
	return (rc);
}