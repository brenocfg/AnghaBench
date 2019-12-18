#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ub_ctx {int /*<<< orphan*/  cfglock; TYPE_1__* env; scalar_t__ finalized; } ;
struct TYPE_4__ {int /*<<< orphan*/  trust_anchor_file_list; } ;
struct TYPE_3__ {TYPE_2__* cfg; } ;

/* Variables and functions */
 int UB_AFTERFINAL ; 
 int UB_NOERROR ; 
 int UB_NOMEM ; 
 int /*<<< orphan*/  cfg_strlist_insert (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  lock_basic_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_basic_unlock (int /*<<< orphan*/ *) ; 
 char* strdup (char const*) ; 

int 
ub_ctx_add_ta_file(struct ub_ctx* ctx, const char* fname)
{
	char* dup = strdup(fname);
	if(!dup) return UB_NOMEM;
	lock_basic_lock(&ctx->cfglock);
	if(ctx->finalized) {
		lock_basic_unlock(&ctx->cfglock);
		free(dup);
		return UB_AFTERFINAL;
	}
	if(!cfg_strlist_insert(&ctx->env->cfg->trust_anchor_file_list, dup)) {
		lock_basic_unlock(&ctx->cfglock);
		return UB_NOMEM;
	}
	lock_basic_unlock(&ctx->cfglock);
	return UB_NOERROR;
}