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
struct dh_ctx {int /*<<< orphan*/  xa; int /*<<< orphan*/  g; int /*<<< orphan*/  q; int /*<<< orphan*/  p; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct dh_ctx*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mpi_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dh_clear_ctx(struct dh_ctx *ctx)
{
	mpi_free(ctx->p);
	mpi_free(ctx->q);
	mpi_free(ctx->g);
	mpi_free(ctx->xa);
	memset(ctx, 0, sizeof(*ctx));
}