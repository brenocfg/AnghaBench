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
struct pack_write_context {int /*<<< orphan*/  stats; int /*<<< orphan*/  indexer; } ;

/* Variables and functions */
 int git_indexer_append (int /*<<< orphan*/ ,void*,size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int write_cb(void *buf, size_t len, void *payload)
{
	struct pack_write_context *ctx = payload;
	return git_indexer_append(ctx->indexer, buf, len, ctx->stats);
}