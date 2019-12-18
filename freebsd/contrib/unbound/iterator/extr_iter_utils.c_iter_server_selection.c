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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int /*<<< orphan*/  time_t ;
struct sock_list {int dummy; } ;
struct module_env {int /*<<< orphan*/  rnd; int /*<<< orphan*/ * now; } ;
struct iter_env {int dummy; } ;
struct delegpt_addr {scalar_t__ attempts; struct delegpt_addr* next_result; } ;
struct delegpt {struct delegpt_addr* result_list; } ;

/* Variables and functions */
 int BLACKLIST_PENALTY ; 
 scalar_t__ OUTBOUND_MSG_RETRY ; 
 int USEFUL_SERVER_TOP_TIMEOUT ; 
 int /*<<< orphan*/  VERB_ALGO ; 
 int iter_filter_order (struct iter_env*,struct module_env*,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct delegpt*,int*,int,struct sock_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_assert (int) ; 
 int ub_random_max (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  verbose (int /*<<< orphan*/ ,char*,...) ; 

struct delegpt_addr* 
iter_server_selection(struct iter_env* iter_env, 
	struct module_env* env, struct delegpt* dp, 
	uint8_t* name, size_t namelen, uint16_t qtype, int* dnssec_lame,
	int* chase_to_rd, int open_target, struct sock_list* blacklist,
	time_t prefetch)
{
	int sel;
	int selrtt;
	struct delegpt_addr* a, *prev;
	int num = iter_filter_order(iter_env, env, name, namelen, qtype,
		*env->now, dp, &selrtt, open_target, blacklist, prefetch);

	if(num == 0)
		return NULL;
	verbose(VERB_ALGO, "selrtt %d", selrtt);
	if(selrtt > BLACKLIST_PENALTY) {
		if(selrtt-BLACKLIST_PENALTY > USEFUL_SERVER_TOP_TIMEOUT*3) {
			verbose(VERB_ALGO, "chase to "
				"blacklisted recursion lame server");
			*chase_to_rd = 1;
		}
		if(selrtt-BLACKLIST_PENALTY > USEFUL_SERVER_TOP_TIMEOUT*2) {
			verbose(VERB_ALGO, "chase to "
				"blacklisted dnssec lame server");
			*dnssec_lame = 1;
		}
	} else {
		if(selrtt > USEFUL_SERVER_TOP_TIMEOUT*3) {
			verbose(VERB_ALGO, "chase to recursion lame server");
			*chase_to_rd = 1;
		}
		if(selrtt > USEFUL_SERVER_TOP_TIMEOUT*2) {
			verbose(VERB_ALGO, "chase to dnssec lame server");
			*dnssec_lame = 1;
		}
		if(selrtt == USEFUL_SERVER_TOP_TIMEOUT) {
			verbose(VERB_ALGO, "chase to blacklisted lame server");
			return NULL;
		}
	}

	if(num == 1) {
		a = dp->result_list;
		if(++a->attempts < OUTBOUND_MSG_RETRY)
			return a;
		dp->result_list = a->next_result;
		return a;
	}

	/* randomly select a target from the list */
	log_assert(num > 1);
	/* grab secure random number, to pick unexpected server.
	 * also we need it to be threadsafe. */
	sel = ub_random_max(env->rnd, num); 
	a = dp->result_list;
	prev = NULL;
	while(sel > 0 && a) {
		prev = a;
		a = a->next_result;
		sel--;
	}
	if(!a)  /* robustness */
		return NULL;
	if(++a->attempts < OUTBOUND_MSG_RETRY)
		return a;
	/* remove it from the delegation point result list */
	if(prev)
		prev->next_result = a->next_result;
	else	dp->result_list = a->next_result;
	return a;
}