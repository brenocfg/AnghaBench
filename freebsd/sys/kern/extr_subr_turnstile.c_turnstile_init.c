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
struct turnstile {int /*<<< orphan*/  ts_lock; int /*<<< orphan*/  ts_free; int /*<<< orphan*/  ts_pending; int /*<<< orphan*/ * ts_blocked; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_INIT (int /*<<< orphan*/ *) ; 
 int MTX_RECURSE ; 
 int MTX_SPIN ; 
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 size_t TS_EXCLUSIVE_QUEUE ; 
 size_t TS_SHARED_QUEUE ; 
 int /*<<< orphan*/  bzero (void*,int) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
turnstile_init(void *mem, int size, int flags)
{
	struct turnstile *ts;

	bzero(mem, size);
	ts = mem;
	TAILQ_INIT(&ts->ts_blocked[TS_EXCLUSIVE_QUEUE]);
	TAILQ_INIT(&ts->ts_blocked[TS_SHARED_QUEUE]);
	TAILQ_INIT(&ts->ts_pending);
	LIST_INIT(&ts->ts_free);
	mtx_init(&ts->ts_lock, "turnstile lock", NULL, MTX_SPIN | MTX_RECURSE);
	return (0);
}