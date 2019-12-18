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
struct roff {scalar_t__ mstackpos; struct mctx* mstack; } ;
struct mctx {int argc; int /*<<< orphan*/ * argv; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 

void
roff_userret(struct roff *r)
{
	struct mctx	*ctx;
	int		 i;

	assert(r->mstackpos >= 0);
	ctx = r->mstack + r->mstackpos;
	for (i = 0; i < ctx->argc; i++)
		free(ctx->argv[i]);
	ctx->argc = 0;
	r->mstackpos--;
}