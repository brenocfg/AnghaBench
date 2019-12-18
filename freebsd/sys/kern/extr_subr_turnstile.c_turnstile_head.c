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
struct turnstile {int /*<<< orphan*/ * ts_blocked; int /*<<< orphan*/  ts_lock; } ;
struct thread {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  MPASS (int) ; 
 struct thread* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int TS_EXCLUSIVE_QUEUE ; 
 int TS_SHARED_QUEUE ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

struct thread *
turnstile_head(struct turnstile *ts, int queue)
{
#ifdef INVARIANTS

	MPASS(ts != NULL);
	MPASS(queue == TS_SHARED_QUEUE || queue == TS_EXCLUSIVE_QUEUE);
	mtx_assert(&ts->ts_lock, MA_OWNED);
#endif
	return (TAILQ_FIRST(&ts->ts_blocked[queue]));
}