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
struct module_qstate {int dummy; } ;
struct iter_qstate {int state; } ;
struct iter_env {int dummy; } ;

/* Variables and functions */
#define  COLLECT_CLASS_STATE 136 
#define  DSNS_FIND_STATE 135 
#define  FINISHED_STATE 134 
#define  INIT_REQUEST_2_STATE 133 
#define  INIT_REQUEST_3_STATE 132 
#define  INIT_REQUEST_STATE 131 
#define  PRIME_RESP_STATE 130 
#define  QUERYTARGETS_STATE 129 
#define  QUERY_RESP_STATE 128 
 int /*<<< orphan*/  VERB_ALGO ; 
 int /*<<< orphan*/  iter_state_to_string (int) ; 
 int /*<<< orphan*/  log_warn (char*,int) ; 
 int processCollectClass (struct module_qstate*,int) ; 
 int processDSNSFind (struct module_qstate*,struct iter_qstate*,int) ; 
 int processFinished (struct module_qstate*,struct iter_qstate*,int) ; 
 int processInitRequest (struct module_qstate*,struct iter_qstate*,struct iter_env*,int) ; 
 int processInitRequest2 (struct module_qstate*,struct iter_qstate*,int) ; 
 int processInitRequest3 (struct module_qstate*,struct iter_qstate*,int) ; 
 int processPrimeResponse (struct module_qstate*,int) ; 
 int processQueryResponse (struct module_qstate*,struct iter_qstate*,int) ; 
 int processQueryTargets (struct module_qstate*,struct iter_qstate*,struct iter_env*,int) ; 
 int /*<<< orphan*/  verbose (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
iter_handle(struct module_qstate* qstate, struct iter_qstate* iq,
	struct iter_env* ie, int id)
{
	int cont = 1;
	while(cont) {
		verbose(VERB_ALGO, "iter_handle processing q with state %s",
			iter_state_to_string(iq->state));
		switch(iq->state) {
			case INIT_REQUEST_STATE:
				cont = processInitRequest(qstate, iq, ie, id);
				break;
			case INIT_REQUEST_2_STATE:
				cont = processInitRequest2(qstate, iq, id);
				break;
			case INIT_REQUEST_3_STATE:
				cont = processInitRequest3(qstate, iq, id);
				break;
			case QUERYTARGETS_STATE:
				cont = processQueryTargets(qstate, iq, ie, id);
				break;
			case QUERY_RESP_STATE:
				cont = processQueryResponse(qstate, iq, id);
				break;
			case PRIME_RESP_STATE:
				cont = processPrimeResponse(qstate, id);
				break;
			case COLLECT_CLASS_STATE:
				cont = processCollectClass(qstate, id);
				break;
			case DSNS_FIND_STATE:
				cont = processDSNSFind(qstate, iq, id);
				break;
			case FINISHED_STATE:
				cont = processFinished(qstate, iq, id);
				break;
			default:
				log_warn("iterator: invalid state: %d",
					iq->state);
				cont = 0;
				break;
		}
	}
}