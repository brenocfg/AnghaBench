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
struct TestContext {int fd; int /*<<< orphan*/ * csb; } ;

/* Variables and functions */
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
context_cleanup(struct TestContext *ctx)
{
	if (ctx->csb) {
		free(ctx->csb);
		ctx->csb = NULL;
	}

	close(ctx->fd);
	ctx->fd = -1;
}