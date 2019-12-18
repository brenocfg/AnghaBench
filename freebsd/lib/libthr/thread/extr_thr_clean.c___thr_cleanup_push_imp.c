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
struct pthread_cleanup {void (* routine ) (void*) ;struct pthread_cleanup* prev; scalar_t__ onheap; void* routine_arg; } ;
struct pthread {struct pthread_cleanup* cleanup; } ;
struct _pthread_cleanup_info {int dummy; } ;

/* Variables and functions */
 struct pthread* _get_curthread () ; 

void
__thr_cleanup_push_imp(void (*routine)(void *), void *arg,
    struct _pthread_cleanup_info *info)
{
	struct pthread	*curthread = _get_curthread();
	struct pthread_cleanup *newbuf;

	newbuf = (void *)info;
	newbuf->routine = routine;
	newbuf->routine_arg = arg;
	newbuf->onheap = 0;
	newbuf->prev = curthread->cleanup;
	curthread->cleanup = newbuf;
}