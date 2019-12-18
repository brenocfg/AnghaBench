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
struct tasklet_worker {int /*<<< orphan*/  head; } ;
struct tasklet_struct {int /*<<< orphan*/  data; int /*<<< orphan*/  (* func ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  count; } ;

/* Variables and functions */
 struct tasklet_struct* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct tasklet_struct*,int /*<<< orphan*/ ) ; 
 struct tasklet_struct* TAILQ_LAST (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct tasklet_struct*,int /*<<< orphan*/ ) ; 
 scalar_t__ TASKLET_ST_CMPSET (struct tasklet_struct*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TASKLET_ST_EXEC ; 
 int /*<<< orphan*/  TASKLET_ST_IDLE ; 
 int /*<<< orphan*/  TASKLET_ST_SET (struct tasklet_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TASKLET_WORKER_LOCK (struct tasklet_worker*) ; 
 int /*<<< orphan*/  TASKLET_WORKER_UNLOCK (struct tasklet_worker*) ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  curthread ; 
 int /*<<< orphan*/  entry ; 
 int /*<<< orphan*/  linux_set_current (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tasklet_list ; 

__attribute__((used)) static void
tasklet_handler(void *arg)
{
	struct tasklet_worker *tw = (struct tasklet_worker *)arg;
	struct tasklet_struct *ts;
	struct tasklet_struct *last;

	linux_set_current(curthread);

	TASKLET_WORKER_LOCK(tw);
	last = TAILQ_LAST(&tw->head, tasklet_list);
	while (1) {
		ts = TAILQ_FIRST(&tw->head);
		if (ts == NULL)
			break;
		TAILQ_REMOVE(&tw->head, ts, entry);

		if (!atomic_read(&ts->count)) {
			TASKLET_WORKER_UNLOCK(tw);
			do {
				/* reset executing state */
				TASKLET_ST_SET(ts, TASKLET_ST_EXEC);

				ts->func(ts->data);

			} while (TASKLET_ST_CMPSET(ts, TASKLET_ST_EXEC,
			        TASKLET_ST_IDLE) == 0);
			TASKLET_WORKER_LOCK(tw);
		} else {
			TAILQ_INSERT_TAIL(&tw->head, ts, entry);
		}
		if (ts == last)
			break;
	}
	TASKLET_WORKER_UNLOCK(tw);
}