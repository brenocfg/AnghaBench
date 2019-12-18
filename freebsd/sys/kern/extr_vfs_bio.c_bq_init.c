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
struct bufqueue {int bq_index; int bq_subqueue; scalar_t__ bq_len; int /*<<< orphan*/  bq_queue; int /*<<< orphan*/  bq_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bq_init(struct bufqueue *bq, int qindex, int subqueue, const char *lockname)
{

	mtx_init(&bq->bq_lock, lockname, NULL, MTX_DEF);
	TAILQ_INIT(&bq->bq_queue);
	bq->bq_len = 0;
	bq->bq_index = qindex;
	bq->bq_subqueue = subqueue;
}