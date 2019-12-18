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
struct ub_ctx {int next_querynum; int /*<<< orphan*/  queries; } ;

/* Variables and functions */
 int /*<<< orphan*/  NUM_ID_TRIES ; 
 scalar_t__ rbtree_search (int /*<<< orphan*/ *,int*) ; 

__attribute__((used)) static int
find_id(struct ub_ctx* ctx, int* id)
{
	size_t tries = 0;
	ctx->next_querynum++;
	while(rbtree_search(&ctx->queries, &ctx->next_querynum)) {
		ctx->next_querynum++; /* numerical wraparound is fine */
		if(tries++ > NUM_ID_TRIES)
			return 0;
	}
	*id = ctx->next_querynum;
	return 1;
}