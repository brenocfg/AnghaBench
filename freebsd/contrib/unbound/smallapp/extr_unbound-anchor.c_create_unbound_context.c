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
struct ub_ctx {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int ub_ctx_config (struct ub_ctx*,char const*) ; 
 struct ub_ctx* ub_ctx_create () ; 
 int /*<<< orphan*/  ub_ctx_error_exit (struct ub_ctx*,char const*,char*) ; 
 int ub_ctx_resolvconf (struct ub_ctx*,char const*) ; 
 int ub_ctx_set_option (struct ub_ctx*,char*,char const*) ; 
 char* ub_strerror (int) ; 
 scalar_t__ verb ; 

__attribute__((used)) static struct ub_ctx* 
create_unbound_context(const char* res_conf, const char* root_hints,
	const char* debugconf, int ip4only, int ip6only)
{
	int r;
	struct ub_ctx* ctx = ub_ctx_create();
	if(!ctx) {
		if(verb) printf("out of memory\n");
		exit(0);
	}
	/* do not waste time and network traffic to fetch extra nameservers */
	r = ub_ctx_set_option(ctx, "target-fetch-policy:", "0 0 0 0 0");
	if(r && verb) printf("ctx targetfetchpolicy: %s\n", ub_strerror(r));
	/* read config file first, so its settings can be overridden */
	if(debugconf) {
		r = ub_ctx_config(ctx, debugconf);
		if(r) ub_ctx_error_exit(ctx, debugconf, ub_strerror(r));
	}
	if(res_conf) {
		r = ub_ctx_resolvconf(ctx, res_conf);
		if(r) ub_ctx_error_exit(ctx, res_conf, ub_strerror(r));
	}
	if(root_hints) {
		r = ub_ctx_set_option(ctx, "root-hints:", root_hints);
		if(r) ub_ctx_error_exit(ctx, root_hints, ub_strerror(r));
	}
	if(ip4only) {
		r = ub_ctx_set_option(ctx, "do-ip6:", "no");
		if(r) ub_ctx_error_exit(ctx, "ip4only", ub_strerror(r));
	}
	if(ip6only) {
		r = ub_ctx_set_option(ctx, "do-ip4:", "no");
		if(r) ub_ctx_error_exit(ctx, "ip6only", ub_strerror(r));
	}
	return ctx;
}