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
struct caam_rng_ctx {int current_buf; struct buf_data* bufs; } ;
struct buf_data {int /*<<< orphan*/  filled; int /*<<< orphan*/  empty; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUF_EMPTY ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int rng_create_job_desc (struct caam_rng_ctx*,int) ; 
 int /*<<< orphan*/  submit_job (struct caam_rng_ctx*,int) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int caam_init_buf(struct caam_rng_ctx *ctx, int buf_id)
{
	struct buf_data *bd = &ctx->bufs[buf_id];
	int err;

	err = rng_create_job_desc(ctx, buf_id);
	if (err)
		return err;

	atomic_set(&bd->empty, BUF_EMPTY);
	submit_job(ctx, buf_id == ctx->current_buf);
	wait_for_completion(&bd->filled);

	return 0;
}