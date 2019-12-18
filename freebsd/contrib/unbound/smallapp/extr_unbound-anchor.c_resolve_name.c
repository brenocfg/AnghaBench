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
struct ip_list {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LDNS_RR_CLASS_IN ; 
 int /*<<< orphan*/  LDNS_RR_TYPE_A ; 
 int /*<<< orphan*/  LDNS_RR_TYPE_AAAA ; 
 struct ub_ctx* create_unbound_context (char const*,char const*,char const*,int,int) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 struct ip_list* parse_ip_addr (char const*,int) ; 
 int /*<<< orphan*/  printf (char*,char const*) ; 
 int /*<<< orphan*/  resolve_host_ip (struct ub_ctx*,char const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ip_list**) ; 
 int /*<<< orphan*/  ub_ctx_delete (struct ub_ctx*) ; 
 scalar_t__ verb ; 

__attribute__((used)) static struct ip_list*
resolve_name(const char* host, int port, const char* res_conf,
	const char* root_hints, const char* debugconf, int ip4only, int ip6only)
{
	struct ub_ctx* ctx;
	struct ip_list* list = NULL;
	/* first see if name is an IP address itself */
	if( (list=parse_ip_addr(host, port)) ) {
		return list;
	}
	
	/* create resolver context */
	ctx = create_unbound_context(res_conf, root_hints, debugconf,
        	ip4only, ip6only);

	/* try resolution of A */
	if(!ip6only) {
		resolve_host_ip(ctx, host, port, LDNS_RR_TYPE_A,
			LDNS_RR_CLASS_IN, &list);
	}

	/* try resolution of AAAA */
	if(!ip4only) {
		resolve_host_ip(ctx, host, port, LDNS_RR_TYPE_AAAA,
			LDNS_RR_CLASS_IN, &list);
	}

	ub_ctx_delete(ctx);
	if(!list) {
		if(verb) printf("%s has no IP addresses I can use\n", host);
		exit(0);
	}
	return list;
}