#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  lqh; } ;
typedef  TYPE_1__ MPOOL ;
typedef  TYPE_1__ BKT ;

/* Variables and functions */
 int RET_SUCCESS ; 
 int /*<<< orphan*/  TAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 TYPE_1__* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  q ; 

int
mpool_close(MPOOL *mp)
{
	BKT *bp;

	/* Free up any space allocated to the lru pages. */
	while (!TAILQ_EMPTY(&mp->lqh)) {
		bp = TAILQ_FIRST(&mp->lqh);
		TAILQ_REMOVE(&mp->lqh, bp, q);
		free(bp);
	}

	/* Free the MPOOL cookie. */
	free(mp);
	return (RET_SUCCESS);
}