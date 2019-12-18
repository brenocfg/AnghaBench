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
struct ub_ctx {int /*<<< orphan*/  cfglock; TYPE_2__* env; scalar_t__ finalized; } ;
struct sockaddr_storage {int dummy; } ;
struct config_stub {int /*<<< orphan*/  addrs; struct config_stub* next; void* name; } ;
typedef  int /*<<< orphan*/  socklen_t ;
struct TYPE_4__ {TYPE_1__* cfg; } ;
struct TYPE_3__ {struct config_stub* forwards; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 int UB_AFTERFINAL ; 
 int UB_NOERROR ; 
 int UB_NOMEM ; 
 int UB_SYNTAX ; 
 struct config_stub* calloc (int,int) ; 
 int /*<<< orphan*/  cfg_strlist_insert (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  config_delstubs (struct config_stub*) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  extstrtoaddr (char const*,struct sockaddr_storage*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (struct config_stub*) ; 
 int /*<<< orphan*/  lock_basic_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_basic_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log_assert (struct config_stub*) ; 
 scalar_t__ strcmp (void*,char*) ; 
 void* strdup (char const*) ; 

int 
ub_ctx_set_fwd(struct ub_ctx* ctx, const char* addr)
{
	struct sockaddr_storage storage;
	socklen_t stlen;
	struct config_stub* s;
	char* dupl;
	lock_basic_lock(&ctx->cfglock);
	if(ctx->finalized) {
		lock_basic_unlock(&ctx->cfglock);
		errno=EINVAL;
		return UB_AFTERFINAL;
	}
	if(!addr) {
		/* disable fwd mode - the root stub should be first. */
		if(ctx->env->cfg->forwards &&
			strcmp(ctx->env->cfg->forwards->name, ".") == 0) {
			s = ctx->env->cfg->forwards;
			ctx->env->cfg->forwards = s->next;
			s->next = NULL;
			config_delstubs(s);
		}
		lock_basic_unlock(&ctx->cfglock);
		return UB_NOERROR;
	}
	lock_basic_unlock(&ctx->cfglock);

	/* check syntax for addr */
	if(!extstrtoaddr(addr, &storage, &stlen)) {
		errno=EINVAL;
		return UB_SYNTAX;
	}
	
	/* it parses, add root stub in front of list */
	lock_basic_lock(&ctx->cfglock);
	if(!ctx->env->cfg->forwards ||
		strcmp(ctx->env->cfg->forwards->name, ".") != 0) {
		s = calloc(1, sizeof(*s));
		if(!s) {
			lock_basic_unlock(&ctx->cfglock);
			errno=ENOMEM;
			return UB_NOMEM;
		}
		s->name = strdup(".");
		if(!s->name) {
			free(s);
			lock_basic_unlock(&ctx->cfglock);
			errno=ENOMEM;
			return UB_NOMEM;
		}
		s->next = ctx->env->cfg->forwards;
		ctx->env->cfg->forwards = s;
	} else {
		log_assert(ctx->env->cfg->forwards);
		s = ctx->env->cfg->forwards;
	}
	dupl = strdup(addr);
	if(!dupl) {
		lock_basic_unlock(&ctx->cfglock);
		errno=ENOMEM;
		return UB_NOMEM;
	}
	if(!cfg_strlist_insert(&s->addrs, dupl)) {
		lock_basic_unlock(&ctx->cfglock);
		errno=ENOMEM;
		return UB_NOMEM;
	}
	lock_basic_unlock(&ctx->cfglock);
	return UB_NOERROR;
}