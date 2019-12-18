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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;
typedef  scalar_t__ time_t ;
struct sock_list {int dummy; } ;
struct module_env {TYPE_1__* cfg; int /*<<< orphan*/  rnd; } ;
struct iter_env {int dummy; } ;
struct TYPE_4__ {scalar_t__ ss_family; } ;
struct delegpt_addr {int sel_rtt; int attempts; struct delegpt_addr* next_result; TYPE_2__ addr; } ;
struct delegpt {struct delegpt_addr* result_list; } ;
struct TYPE_3__ {scalar_t__ fast_server_permil; size_t fast_server_num; scalar_t__ prefer_ip6; } ;

/* Variables and functions */
 scalar_t__ AF_INET6 ; 
 int RTT_BAND ; 
 int USEFUL_SERVER_TOP_TIMEOUT ; 
 int /*<<< orphan*/  VERB_ALGO ; 
 scalar_t__ delegpt_count_missing_targets (struct delegpt*) ; 
 int iter_fill_rtt (struct iter_env*,struct module_env*,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ,scalar_t__,struct delegpt*,int*,struct sock_list*,size_t*) ; 
 int nth_rtt (struct delegpt_addr*,size_t,size_t) ; 
 scalar_t__ ub_random_max (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  verbose (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
iter_filter_order(struct iter_env* iter_env, struct module_env* env,
	uint8_t* name, size_t namelen, uint16_t qtype, time_t now, 
	struct delegpt* dp, int* selected_rtt, int open_target, 
	struct sock_list* blacklist, time_t prefetch)
{
	int got_num = 0, low_rtt = 0, swap_to_front, rtt_band = RTT_BAND, nth;
	size_t num_results;
	struct delegpt_addr* a, *n, *prev=NULL;

	/* fillup sel_rtt and find best rtt in the bunch */
	got_num = iter_fill_rtt(iter_env, env, name, namelen, qtype, now, dp, 
		&low_rtt, blacklist, &num_results);
	if(got_num == 0) 
		return 0;
	if(low_rtt >= USEFUL_SERVER_TOP_TIMEOUT &&
		(delegpt_count_missing_targets(dp) > 0 || open_target > 0)) {
		verbose(VERB_ALGO, "Bad choices, trying to get more choice");
		return 0; /* we want more choice. The best choice is a bad one.
			     return 0 to force the caller to fetch more */
	}

	if(env->cfg->fast_server_permil != 0 && prefetch == 0 &&
		num_results > env->cfg->fast_server_num &&
		ub_random_max(env->rnd, 1000) < env->cfg->fast_server_permil) {
		/* the query is not prefetch, but for a downstream client,
		 * there are more servers available then the fastest N we want
		 * to choose from. Limit our choice to the fastest servers. */
		nth = nth_rtt(dp->result_list, num_results,
			env->cfg->fast_server_num);
		if(nth > 0) {
			rtt_band = nth - low_rtt;
			if(rtt_band > RTT_BAND)
				rtt_band = RTT_BAND;
		}
	}

	got_num = 0;
	a = dp->result_list;
	while(a) {
		/* skip unsuitable targets */
		if(a->sel_rtt == -1) {
			prev = a;
			a = a->next_result;
			continue;
		}
		/* classify the server address and determine what to do */
		swap_to_front = 0;
		if(a->sel_rtt >= low_rtt && a->sel_rtt - low_rtt <= rtt_band) {
			got_num++;
			swap_to_front = 1;
		} else if(a->sel_rtt<low_rtt && low_rtt-a->sel_rtt<=rtt_band) {
			got_num++;
			swap_to_front = 1;
		}
		/* swap to front if necessary, or move to next result */
		if(swap_to_front && prev) {
			n = a->next_result;
			prev->next_result = n;
			a->next_result = dp->result_list;
			dp->result_list = a;
			a = n;
		} else {
			prev = a;
			a = a->next_result;
		}
	}
	*selected_rtt = low_rtt;

	if (env->cfg->prefer_ip6) {
		int got_num6 = 0;
		int low_rtt6 = 0;
		int i;
		int attempt = -1; /* filter to make sure addresses have
		  less attempts on them than the first, to force round
		  robin when all the IPv6 addresses fail */
		int num4ok = 0; /* number ip4 at low attempt count */
		int num4_lowrtt = 0;
		prev = NULL;
		a = dp->result_list;
		for(i = 0; i < got_num; i++) {
			swap_to_front = 0;
			if(a->addr.ss_family != AF_INET6 && attempt == -1) {
				/* if we only have ip4 at low attempt count,
				 * then ip6 is failing, and we need to
				 * select one of the remaining IPv4 addrs */
				attempt = a->attempts;
				num4ok++;
				num4_lowrtt = a->sel_rtt;
			} else if(a->addr.ss_family != AF_INET6 && attempt == a->attempts) {
				num4ok++;
				if(num4_lowrtt == 0 || a->sel_rtt < num4_lowrtt) {
					num4_lowrtt = a->sel_rtt;
				}
			}
			if(a->addr.ss_family == AF_INET6) {
				if(attempt == -1) {
					attempt = a->attempts;
				} else if(a->attempts > attempt) {
					break;
				}
				got_num6++;
				swap_to_front = 1;
				if(low_rtt6 == 0 || a->sel_rtt < low_rtt6) {
					low_rtt6 = a->sel_rtt;
				}
			}
			/* swap to front if IPv6, or move to next result */
			if(swap_to_front && prev) {
				n = a->next_result;
				prev->next_result = n;
				a->next_result = dp->result_list;
				dp->result_list = a;
				a = n;
			} else {
				prev = a;
				a = a->next_result;
			}
		}
		if(got_num6 > 0) {
			got_num = got_num6;
			*selected_rtt = low_rtt6;
		} else if(num4ok > 0) {
			got_num = num4ok;
			*selected_rtt = num4_lowrtt;
		}
	}
	return got_num;
}