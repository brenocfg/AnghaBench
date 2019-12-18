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
struct torus_context {scalar_t__ torus; int /*<<< orphan*/  fabric; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct torus_context*) ; 
 int /*<<< orphan*/  teardown_fabric (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  teardown_torus (scalar_t__) ; 

__attribute__((used)) static
void torus_context_delete(void *context)
{
	struct torus_context *ctx = context;

	teardown_fabric(&ctx->fabric);
	if (ctx->torus)
		teardown_torus(ctx->torus);
	free(ctx);
}