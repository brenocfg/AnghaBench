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
struct pthread_cleanup {scalar_t__ onheap; int /*<<< orphan*/  routine_arg; int /*<<< orphan*/  (* routine ) (int /*<<< orphan*/ ) ;struct pthread_cleanup* prev; } ;
struct pthread {struct pthread_cleanup* cleanup; } ;

/* Variables and functions */
 struct pthread* _get_curthread () ; 
 int /*<<< orphan*/  free (struct pthread_cleanup*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

void
__thr_cleanup_pop_imp(int execute)
{
	struct pthread	*curthread = _get_curthread();
	struct pthread_cleanup *old;

	if ((old = curthread->cleanup) != NULL) {
		curthread->cleanup = old->prev;
		if (execute)
			old->routine(old->routine_arg);
		if (old->onheap)
			free(old);
	}
}