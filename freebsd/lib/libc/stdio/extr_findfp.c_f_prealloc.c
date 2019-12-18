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
struct glue {struct glue* next; scalar_t__ niobs; } ;

/* Variables and functions */
 int FOPEN_MAX ; 
 int /*<<< orphan*/  SET_GLUE_PTR (struct glue*,struct glue*) ; 
 int /*<<< orphan*/  STDIO_THREAD_LOCK () ; 
 int /*<<< orphan*/  STDIO_THREAD_UNLOCK () ; 
 struct glue __sglue ; 
 int getdtablesize () ; 
 struct glue* lastglue ; 
 struct glue* moreglue (int) ; 

void
f_prealloc(void)
{
	struct glue *g;
	int n;

	n = getdtablesize() - FOPEN_MAX + 20;		/* 20 for slop. */
	/*
	 * It should be safe to walk the list without locking it;
	 * new nodes are only added to the end and none are ever
	 * removed.
	 */
	for (g = &__sglue; (n -= g->niobs) > 0 && g->next; g = g->next)
		/* void */;
	if ((n > 0) && ((g = moreglue(n)) != NULL)) {
		STDIO_THREAD_LOCK();
		SET_GLUE_PTR(lastglue->next, g);
		lastglue = g;
		STDIO_THREAD_UNLOCK();
	}
}