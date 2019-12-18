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
struct evthread_win32_cond {int /*<<< orphan*/  event; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DeleteCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mm_free (struct evthread_win32_cond*) ; 

__attribute__((used)) static void
evthread_win32_cond_free(void *cond_)
{
	struct evthread_win32_cond *cond = cond_;
	DeleteCriticalSection(&cond->lock);
	CloseHandle(cond->event);
	mm_free(cond);
}