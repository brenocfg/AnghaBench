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
typedef  int /*<<< orphan*/  thrd_t ;
typedef  int /*<<< orphan*/  thrd_start_t ;
struct thrd_param {void* arg; int /*<<< orphan*/  func; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct thrd_param*) ; 
 struct thrd_param* malloc (int) ; 
 scalar_t__ pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct thrd_param*) ; 
 int /*<<< orphan*/  thrd_entry ; 
 int thrd_error ; 
 int thrd_nomem ; 
 int thrd_success ; 

int
thrd_create(thrd_t *thr, thrd_start_t func, void *arg)
{
	struct thrd_param *tp;

	/*
	 * Work around return type inconsistency.  Wrap execution using
	 * a function conforming to pthread_create()'s start_routine.
	 */
	tp = malloc(sizeof(*tp));
	if (tp == NULL)
		return (thrd_nomem);
	tp->func = func;
	tp->arg = arg;
	if (pthread_create(thr, NULL, thrd_entry, tp) != 0) {
		free(tp);
		return (thrd_error);
	}
	return (thrd_success);
}