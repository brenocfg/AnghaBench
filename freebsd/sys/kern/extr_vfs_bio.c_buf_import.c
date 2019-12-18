#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct buf {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  bq_queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  BQ_LOCK (TYPE_1__*) ; 
 int /*<<< orphan*/  BQ_UNLOCK (TYPE_1__*) ; 
 struct buf* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bq_remove (TYPE_1__*,struct buf*) ; 
 TYPE_1__ bqempty ; 

__attribute__((used)) static int
buf_import(void *arg, void **store, int cnt, int domain, int flags)
{
	struct buf *bp;
	int i;

	BQ_LOCK(&bqempty);
	for (i = 0; i < cnt; i++) {
		bp = TAILQ_FIRST(&bqempty.bq_queue);
		if (bp == NULL)
			break;
		bq_remove(&bqempty, bp);
		store[i] = bp;
	}
	BQ_UNLOCK(&bqempty);

	return (i);
}