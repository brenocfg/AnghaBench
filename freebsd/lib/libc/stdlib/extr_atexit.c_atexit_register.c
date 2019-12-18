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
struct atexit_fn {int dummy; } ;
struct atexit {scalar_t__ ind; struct atexit_fn* fns; struct atexit* next; } ;

/* Variables and functions */
 scalar_t__ ATEXIT_SIZE ; 
 int /*<<< orphan*/  _MUTEX_LOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _MUTEX_UNLOCK (int /*<<< orphan*/ *) ; 
 struct atexit* __atexit ; 
 int /*<<< orphan*/  atexit_mutex ; 
 int /*<<< orphan*/  free (struct atexit*) ; 
 scalar_t__ malloc (int) ; 

__attribute__((used)) static int
atexit_register(struct atexit_fn *fptr)
{
	static struct atexit __atexit0;	/* one guaranteed table */
	struct atexit *p;

	_MUTEX_LOCK(&atexit_mutex);
	if ((p = __atexit) == NULL)
		__atexit = p = &__atexit0;
	else while (p->ind >= ATEXIT_SIZE) {
		struct atexit *old__atexit;
		old__atexit = __atexit;
	        _MUTEX_UNLOCK(&atexit_mutex);
		if ((p = (struct atexit *)malloc(sizeof(*p))) == NULL)
			return (-1);
		_MUTEX_LOCK(&atexit_mutex);
		if (old__atexit != __atexit) {
			/* Lost race, retry operation */
			_MUTEX_UNLOCK(&atexit_mutex);
			free(p);
			_MUTEX_LOCK(&atexit_mutex);
			p = __atexit;
			continue;
		}
		p->ind = 0;
		p->next = __atexit;
		__atexit = p;
	}
	p->fns[p->ind++] = *fptr;
	_MUTEX_UNLOCK(&atexit_mutex);
	return 0;
}