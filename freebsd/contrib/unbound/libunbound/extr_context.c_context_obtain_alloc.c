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
struct alloc_cache {struct alloc_cache* super; } ;
struct ub_ctx {struct alloc_cache superalloc; int /*<<< orphan*/  cfglock; int /*<<< orphan*/  thr_next_num; struct alloc_cache* alloc_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  alloc_init (struct alloc_cache*,struct alloc_cache*,int) ; 
 scalar_t__ calloc (int,int) ; 
 int /*<<< orphan*/  lock_basic_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_basic_unlock (int /*<<< orphan*/ *) ; 

struct alloc_cache* 
context_obtain_alloc(struct ub_ctx* ctx, int locking)
{
	struct alloc_cache* a;
	int tnum = 0;
	if(locking) {
		lock_basic_lock(&ctx->cfglock);
	}
	a = ctx->alloc_list;
	if(a)
		ctx->alloc_list = a->super; /* snip off list */
	else	tnum = ctx->thr_next_num++;
	if(locking) {
		lock_basic_unlock(&ctx->cfglock);
	}
	if(a) {
		a->super = &ctx->superalloc;
		return a;
	}
	a = (struct alloc_cache*)calloc(1, sizeof(*a));
	if(!a)
		return NULL;
	alloc_init(a, &ctx->superalloc, tnum);
	return a;
}