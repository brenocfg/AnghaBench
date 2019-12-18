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
struct evrpc_hook_meta {int /*<<< orphan*/  meta_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  evrpc_meta_data_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mm_free (struct evrpc_hook_meta*) ; 

__attribute__((used)) static void
evrpc_hook_context_free_(struct evrpc_hook_meta *ctx)
{
	evrpc_meta_data_free(&ctx->meta_data);
	mm_free(ctx);
}