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
struct iter_forwards {int dummy; } ;
struct delegpt {void* ssl_upstream; int /*<<< orphan*/  no_cache; void* has_parent_side_NS; } ;
struct config_stub {scalar_t__ ssl_upstream; int /*<<< orphan*/  no_cache; int /*<<< orphan*/  isfirst; struct config_stub* next; } ;
struct config_file {struct config_stub* forwards; } ;

/* Variables and functions */
 int /*<<< orphan*/  LDNS_RR_CLASS_IN ; 
 int /*<<< orphan*/  VERB_QUERY ; 
 int /*<<< orphan*/  delegpt_free_mlc (struct delegpt*) ; 
 int /*<<< orphan*/  delegpt_log (int /*<<< orphan*/ ,struct delegpt*) ; 
 int /*<<< orphan*/  forwards_insert (struct iter_forwards*,int /*<<< orphan*/ ,struct delegpt*) ; 
 int /*<<< orphan*/  read_fwds_addr (struct config_stub*,struct delegpt*) ; 
 int /*<<< orphan*/  read_fwds_host (struct config_stub*,struct delegpt*) ; 
 struct delegpt* read_fwds_name (struct config_stub*) ; 
 int /*<<< orphan*/  verbose (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int 
read_forwards(struct iter_forwards* fwd, struct config_file* cfg)
{
	struct config_stub* s;
	for(s = cfg->forwards; s; s = s->next) {
		struct delegpt* dp;
		if(!(dp=read_fwds_name(s)))
			return 0;
		if(!read_fwds_host(s, dp) || !read_fwds_addr(s, dp)) {
			delegpt_free_mlc(dp);
			return 0;
		}
		/* set flag that parent side NS information is included.
		 * Asking a (higher up) server on the internet is not useful */
		/* the flag is turned off for 'forward-first' so that the
		 * last resort will ask for parent-side NS record and thus
		 * fallback to the internet name servers on a failure */
		dp->has_parent_side_NS = (uint8_t)!s->isfirst;
		/* Do not cache if set. */
		dp->no_cache = s->no_cache;
		/* use SSL for queries to this forwarder */
		dp->ssl_upstream = (uint8_t)s->ssl_upstream;
		verbose(VERB_QUERY, "Forward zone server list:");
		delegpt_log(VERB_QUERY, dp);
		if(!forwards_insert(fwd, LDNS_RR_CLASS_IN, dp))
			return 0;
	}
	return 1;
}