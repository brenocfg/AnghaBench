#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct module_env {size_t edns_known_options_num; TYPE_1__* edns_known_options; } ;
typedef  int /*<<< orphan*/  str ;
typedef  enum verbosity_value { ____Placeholder_verbosity_value } verbosity_value ;
struct TYPE_2__ {scalar_t__ no_aggregation; scalar_t__ bypass_cache_stage; int /*<<< orphan*/  opt_code; } ;

/* Variables and functions */
 int /*<<< orphan*/  sldns_wire2str_edns_option_code_print (char**,size_t*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  verbose (int,char*,...) ; 
 int verbosity ; 

void
log_edns_known_options(enum verbosity_value level, struct module_env* env)
{
	size_t i;
	char str[32], *s;
	size_t slen;
	if(env->edns_known_options_num > 0 && verbosity >= level) {
		verbose(level, "EDNS known options:");
		verbose(level, "  Code:    Bypass_cache_stage: Aggregate_mesh:");
		for(i=0; i<env->edns_known_options_num; i++) {
			s = str;
			slen = sizeof(str);
			(void)sldns_wire2str_edns_option_code_print(&s, &slen,
				env->edns_known_options[i].opt_code);
			verbose(level, "  %-8.8s %-19s %-15s", str,
				env->edns_known_options[i].bypass_cache_stage?"YES":"NO",
				env->edns_known_options[i].no_aggregation?"NO":"YES");
		}
	}
}