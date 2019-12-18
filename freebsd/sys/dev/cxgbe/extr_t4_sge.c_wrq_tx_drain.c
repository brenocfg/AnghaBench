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
struct sge_eq {int dummy; } ;
struct sge_wrq {int /*<<< orphan*/  adapter; int /*<<< orphan*/  wr_list; int /*<<< orphan*/  incomplete_wrs; struct sge_eq eq; } ;

/* Variables and functions */
 int /*<<< orphan*/  EQ_LOCK (struct sge_eq*) ; 
 int /*<<< orphan*/  EQ_UNLOCK (struct sge_eq*) ; 
 int /*<<< orphan*/  STAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 scalar_t__ TAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drain_wrq_wr_list (int /*<<< orphan*/ ,struct sge_wrq*) ; 

__attribute__((used)) static void
wrq_tx_drain(void *arg, int n)
{
	struct sge_wrq *wrq = arg;
	struct sge_eq *eq = &wrq->eq;

	EQ_LOCK(eq);
	if (TAILQ_EMPTY(&wrq->incomplete_wrs) && !STAILQ_EMPTY(&wrq->wr_list))
		drain_wrq_wr_list(wrq->adapter, wrq);
	EQ_UNLOCK(eq);
}