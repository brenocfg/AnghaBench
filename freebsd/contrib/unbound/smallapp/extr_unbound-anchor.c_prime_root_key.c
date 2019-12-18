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
struct ub_result {int dummy; } ;
struct ub_ctx {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LDNS_RR_CLASS_IN ; 
 int /*<<< orphan*/  LDNS_RR_TYPE_DNSKEY ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  ub_ctx_delete (struct ub_ctx*) ; 
 int ub_resolve (struct ub_ctx*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ub_result**) ; 
 char* ub_strerror (int) ; 
 scalar_t__ verb ; 

__attribute__((used)) static struct ub_result*
prime_root_key(struct ub_ctx* ctx)
{
	struct ub_result* res = NULL;
	int r;
	r = ub_resolve(ctx, ".", LDNS_RR_TYPE_DNSKEY, LDNS_RR_CLASS_IN, &res);
	if(r) {
		if(verb) printf("resolve DNSKEY: %s\n", ub_strerror(r));
		ub_ctx_delete(ctx);
		exit(0);
	}
	if(!res) {
		if(verb) printf("out of memory\n");
		ub_ctx_delete(ctx);
		exit(0);
	}
	return res;
}