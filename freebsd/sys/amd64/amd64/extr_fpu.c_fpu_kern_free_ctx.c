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
struct fpu_kern_ctx {int flags; } ;

/* Variables and functions */
 int FPU_KERN_CTX_INUSE ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  M_FPUKERN_CTX ; 
 int /*<<< orphan*/  free (struct fpu_kern_ctx*,int /*<<< orphan*/ ) ; 

void
fpu_kern_free_ctx(struct fpu_kern_ctx *ctx)
{

	KASSERT((ctx->flags & FPU_KERN_CTX_INUSE) == 0, ("free'ing inuse ctx"));
	/* XXXKIB clear the memory ? */
	free(ctx, M_FPUKERN_CTX);
}