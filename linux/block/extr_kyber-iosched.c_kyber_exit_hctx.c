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
struct kyber_hctx_data {struct kyber_hctx_data* kcqs; int /*<<< orphan*/ * kcq_map; } ;
struct blk_mq_hw_ctx {struct kyber_hctx_data* sched_data; } ;

/* Variables and functions */
 int KYBER_NUM_DOMAINS ; 
 int /*<<< orphan*/  kfree (struct kyber_hctx_data*) ; 
 int /*<<< orphan*/  sbitmap_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void kyber_exit_hctx(struct blk_mq_hw_ctx *hctx, unsigned int hctx_idx)
{
	struct kyber_hctx_data *khd = hctx->sched_data;
	int i;

	for (i = 0; i < KYBER_NUM_DOMAINS; i++)
		sbitmap_free(&khd->kcq_map[i]);
	kfree(khd->kcqs);
	kfree(hctx->sched_data);
}