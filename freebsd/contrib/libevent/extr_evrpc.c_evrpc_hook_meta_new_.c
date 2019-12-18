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
struct evrpc_hook_meta {int /*<<< orphan*/ * evcon; int /*<<< orphan*/  meta_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  EVUTIL_ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 struct evrpc_hook_meta* mm_malloc (int) ; 

__attribute__((used)) static struct evrpc_hook_meta *
evrpc_hook_meta_new_(void)
{
	struct evrpc_hook_meta *ctx;
	ctx = mm_malloc(sizeof(struct evrpc_hook_meta));
	EVUTIL_ASSERT(ctx != NULL);

	TAILQ_INIT(&ctx->meta_data);
	ctx->evcon = NULL;

	return (ctx);
}