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
typedef  void* uint8_t ;
struct iter_hints {int dummy; } ;
struct delegpt {void* ssl_upstream; int /*<<< orphan*/  no_cache; void* has_parent_side_NS; } ;
struct config_stub {int /*<<< orphan*/  isprime; scalar_t__ ssl_upstream; int /*<<< orphan*/  no_cache; int /*<<< orphan*/  isfirst; struct config_stub* next; } ;
struct config_file {struct config_stub* stubs; } ;

/* Variables and functions */
 int /*<<< orphan*/  LDNS_RR_CLASS_IN ; 
 int /*<<< orphan*/  VERB_QUERY ; 
 int /*<<< orphan*/  delegpt_free_mlc (struct delegpt*) ; 
 int /*<<< orphan*/  delegpt_log (int /*<<< orphan*/ ,struct delegpt*) ; 
 int /*<<< orphan*/  hints_insert (struct iter_hints*,int /*<<< orphan*/ ,struct delegpt*,int) ; 
 int /*<<< orphan*/  read_stubs_addr (struct config_stub*,struct delegpt*) ; 
 int /*<<< orphan*/  read_stubs_host (struct config_stub*,struct delegpt*) ; 
 struct delegpt* read_stubs_name (struct config_stub*) ; 

__attribute__((used)) static int 
read_stubs(struct iter_hints* hints, struct config_file* cfg)
{
	struct config_stub* s;
	struct delegpt* dp;
	for(s = cfg->stubs; s; s = s->next) {
		if(!(dp=read_stubs_name(s)))
			return 0;
		if(!read_stubs_host(s, dp) || !read_stubs_addr(s, dp)) {
			delegpt_free_mlc(dp);
			return 0;
		}
		/* the flag is turned off for 'stub-first' so that the
		 * last resort will ask for parent-side NS record and thus
		 * fallback to the internet name servers on a failure */
		dp->has_parent_side_NS = (uint8_t)!s->isfirst;
		/* Do not cache if set. */
		dp->no_cache = s->no_cache;
		/* ssl_upstream */
		dp->ssl_upstream = (uint8_t)s->ssl_upstream;
		delegpt_log(VERB_QUERY, dp);
		if(!hints_insert(hints, LDNS_RR_CLASS_IN, dp, !s->isprime))
			return 0;
	}
	return 1;
}