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
struct dquot {int /*<<< orphan*/  dq_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_DQUOT ; 
 struct dquot* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct dquot*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dq_freelist ; 
 int /*<<< orphan*/  dqfreelist ; 
 int /*<<< orphan*/  dqhash ; 
 int /*<<< orphan*/  dqhashtbl ; 
 int /*<<< orphan*/  dqhlock ; 
 int /*<<< orphan*/  free (struct dquot*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hashdestroy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 

void
dquninit(void)
{
	struct dquot *dq;

	hashdestroy(dqhashtbl, M_DQUOT, dqhash);
	while ((dq = TAILQ_FIRST(&dqfreelist)) != NULL) {
		TAILQ_REMOVE(&dqfreelist, dq, dq_freelist);
		mtx_destroy(&dq->dq_lock);
		free(dq, M_DQUOT);
	}
	mtx_destroy(&dqhlock);
}