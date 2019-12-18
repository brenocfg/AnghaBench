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
struct alq {struct alq* aq_entbuf; int /*<<< orphan*/  aq_mtx; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_ALD ; 
 int /*<<< orphan*/  alq_shutdown (struct alq*) ; 
 int /*<<< orphan*/  free (struct alq*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 

void
alq_destroy(struct alq *alq)
{
	/* Drain all pending IO. */
	alq_shutdown(alq);

	mtx_destroy(&alq->aq_mtx);
	free(alq->aq_entbuf, M_ALD);
	free(alq, M_ALD);
}