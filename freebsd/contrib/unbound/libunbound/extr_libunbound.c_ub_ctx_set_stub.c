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
struct config_stub {int isprime; int /*<<< orphan*/  addrs; struct config_stub* next; void* name; } ;
typedef  struct config_stub uint8_t ;
struct ub_ctx {int /*<<< orphan*/  cfglock; TYPE_2__* env; scalar_t__ finalized; } ;
struct sockaddr_storage {int dummy; } ;
typedef  int /*<<< orphan*/  socklen_t ;
struct TYPE_4__ {TYPE_1__* cfg; } ;
struct TYPE_3__ {struct config_stub* stubs; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 int UB_AFTERFINAL ; 
 int UB_NOERROR ; 
 int UB_NOMEM ; 
 int UB_SYNTAX ; 
 scalar_t__ calloc (int,int) ; 
 int /*<<< orphan*/  cfg_strlist_insert (int /*<<< orphan*/ *,char*) ; 
 struct config_stub* cfg_stub_find (struct config_stub***,char const*) ; 
 int /*<<< orphan*/  config_delstub (struct config_stub*) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  extstrtoaddr (char const*,struct sockaddr_storage*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (struct config_stub*) ; 
 int /*<<< orphan*/  lock_basic_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_basic_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  parse_dname (char const*,struct config_stub**,size_t*,int*) ; 
 void* strdup (char const*) ; 

int ub_ctx_set_stub(struct ub_ctx* ctx, const char* zone, const char* addr,
	int isprime)
{
	char* a;
	struct config_stub **prev, *elem;

	/* check syntax for zone name */
	if(zone) {
		uint8_t* nm;
		int nmlabs;
		size_t nmlen;
		if(!parse_dname(zone, &nm, &nmlen, &nmlabs)) {
			errno=EINVAL;
			return UB_SYNTAX;
		}
		free(nm);
	} else {
		zone = ".";
	}

	/* check syntax for addr (if not NULL) */
	if(addr) {
		struct sockaddr_storage storage;
		socklen_t stlen;
		if(!extstrtoaddr(addr, &storage, &stlen)) {
			errno=EINVAL;
			return UB_SYNTAX;
		}
	}

	lock_basic_lock(&ctx->cfglock);
	if(ctx->finalized) {
		lock_basic_unlock(&ctx->cfglock);
		errno=EINVAL;
		return UB_AFTERFINAL;
	}

	/* arguments all right, now find or add the stub */
	prev = &ctx->env->cfg->stubs;
	elem = cfg_stub_find(&prev, zone);
	if(!elem && !addr) {
		/* not found and we want to delete, nothing to do */
		lock_basic_unlock(&ctx->cfglock);
		return UB_NOERROR;
	} else if(elem && !addr) {
		/* found, and we want to delete */
		*prev = elem->next;
		config_delstub(elem);
		lock_basic_unlock(&ctx->cfglock);
		return UB_NOERROR;
	} else if(!elem) {
		/* not found, create the stub entry */
		elem=(struct config_stub*)calloc(1, sizeof(struct config_stub));
		if(elem) elem->name = strdup(zone);
		if(!elem || !elem->name) {
			free(elem);
			lock_basic_unlock(&ctx->cfglock);
			errno = ENOMEM;
			return UB_NOMEM;
		}
		elem->next = ctx->env->cfg->stubs;
		ctx->env->cfg->stubs = elem;
	}

	/* add the address to the list and set settings */
	elem->isprime = isprime;
	a = strdup(addr);
	if(!a) {
		lock_basic_unlock(&ctx->cfglock);
		errno = ENOMEM;
		return UB_NOMEM;
	}
	if(!cfg_strlist_insert(&elem->addrs, a)) {
		lock_basic_unlock(&ctx->cfglock);
		errno = ENOMEM;
		return UB_NOMEM;
	}
	lock_basic_unlock(&ctx->cfglock);
	return UB_NOERROR;
}