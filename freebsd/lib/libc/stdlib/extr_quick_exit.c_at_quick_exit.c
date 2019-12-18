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
struct quick_exit_handler {void (* cleanup ) () ;struct quick_exit_handler* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  __compiler_membar () ; 
 int /*<<< orphan*/  atexit_mutex ; 
 struct quick_exit_handler* handlers ; 
 struct quick_exit_handler* malloc (int) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

int
at_quick_exit(void (*func)(void))
{
	struct quick_exit_handler *h;
	
	h = malloc(sizeof(*h));

	if (NULL == h)
		return (1);
	h->cleanup = func;
	pthread_mutex_lock(&atexit_mutex);
	h->next = handlers;
	__compiler_membar();
	handlers = h;
	pthread_mutex_unlock(&atexit_mutex);
	return (0);
}