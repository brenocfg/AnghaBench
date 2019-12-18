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
struct ub_ctx {int /*<<< orphan*/  queries; int /*<<< orphan*/  mods; scalar_t__ need_to_validate; struct ub_ctx* env; int /*<<< orphan*/ * worker; int /*<<< orphan*/  superalloc; int /*<<< orphan*/ * alloc; int /*<<< orphan*/  seed_rnd; int /*<<< orphan*/  cfg; int /*<<< orphan*/  auth_zones; int /*<<< orphan*/  cfglock; int /*<<< orphan*/  rrpipe_lock; int /*<<< orphan*/  qqpipe_lock; } ;
struct module_env {int /*<<< orphan*/  queries; int /*<<< orphan*/  mods; scalar_t__ need_to_validate; struct module_env* env; int /*<<< orphan*/ * worker; int /*<<< orphan*/  superalloc; int /*<<< orphan*/ * alloc; int /*<<< orphan*/  seed_rnd; int /*<<< orphan*/  cfg; int /*<<< orphan*/  auth_zones; int /*<<< orphan*/  cfglock; int /*<<< orphan*/  rrpipe_lock; int /*<<< orphan*/  qqpipe_lock; } ;
typedef  int /*<<< orphan*/  seed ;
typedef  int /*<<< orphan*/  WSADATA ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  MAKEWORD (int,int) ; 
 int WSAStartup (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  alloc_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  auth_zones_create () ; 
 scalar_t__ calloc (int,int) ; 
 int /*<<< orphan*/  checklock_start () ; 
 int /*<<< orphan*/  config_create_forlib () ; 
 int /*<<< orphan*/  config_delete (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  context_query_cmp ; 
 int /*<<< orphan*/  edns_known_options_delete (struct ub_ctx*) ; 
 int /*<<< orphan*/  edns_known_options_init (struct ub_ctx*) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  explicit_bzero (unsigned int*,int) ; 
 int /*<<< orphan*/  free (struct ub_ctx*) ; 
 scalar_t__ getpid () ; 
 int /*<<< orphan*/  lock_basic_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log_err (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_ident_set (char*) ; 
 int /*<<< orphan*/  log_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  modstack_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rbtree_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ time (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ub_initstate (unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ub_randfree (int /*<<< orphan*/ ) ; 
 scalar_t__ verbosity ; 
 int /*<<< orphan*/  wsa_strerror (int) ; 

__attribute__((used)) static struct ub_ctx* ub_ctx_create_nopipe(void)
{
	struct ub_ctx* ctx;
	unsigned int seed;
#ifdef USE_WINSOCK
	int r;
	WSADATA wsa_data;
#endif
	
	checklock_start();
	log_init(NULL, 0, NULL); /* logs to stderr */
	log_ident_set("libunbound");
#ifdef USE_WINSOCK
	if((r = WSAStartup(MAKEWORD(2,2), &wsa_data)) != 0) {
		log_err("could not init winsock. WSAStartup: %s",
			wsa_strerror(r));
		return NULL;
	}
#endif
	verbosity = 0; /* errors only */
	checklock_start();
	ctx = (struct ub_ctx*)calloc(1, sizeof(*ctx));
	if(!ctx) {
		errno = ENOMEM;
		return NULL;
	}
	alloc_init(&ctx->superalloc, NULL, 0);
	seed = (unsigned int)time(NULL) ^ (unsigned int)getpid();
	if(!(ctx->seed_rnd = ub_initstate(seed, NULL))) {
		explicit_bzero(&seed, sizeof(seed));
		ub_randfree(ctx->seed_rnd);
		free(ctx);
		errno = ENOMEM;
		return NULL;
	}
	explicit_bzero(&seed, sizeof(seed));
	lock_basic_init(&ctx->qqpipe_lock);
	lock_basic_init(&ctx->rrpipe_lock);
	lock_basic_init(&ctx->cfglock);
	ctx->env = (struct module_env*)calloc(1, sizeof(*ctx->env));
	if(!ctx->env) {
		ub_randfree(ctx->seed_rnd);
		free(ctx);
		errno = ENOMEM;
		return NULL;
	}
	ctx->env->cfg = config_create_forlib();
	if(!ctx->env->cfg) {
		free(ctx->env);
		ub_randfree(ctx->seed_rnd);
		free(ctx);
		errno = ENOMEM;
		return NULL;
	}
	/* init edns_known_options */
	if(!edns_known_options_init(ctx->env)) {
		config_delete(ctx->env->cfg);
		free(ctx->env);
		ub_randfree(ctx->seed_rnd);
		free(ctx);
		errno = ENOMEM;
		return NULL;
	}
	ctx->env->auth_zones = auth_zones_create();
	if(!ctx->env->auth_zones) {
		edns_known_options_delete(ctx->env);
		config_delete(ctx->env->cfg);
		free(ctx->env);
		ub_randfree(ctx->seed_rnd);
		free(ctx);
		errno = ENOMEM;
		return NULL;
	}
	ctx->env->alloc = &ctx->superalloc;
	ctx->env->worker = NULL;
	ctx->env->need_to_validate = 0;
	modstack_init(&ctx->mods);
	rbtree_init(&ctx->queries, &context_query_cmp);
	return ctx;
}