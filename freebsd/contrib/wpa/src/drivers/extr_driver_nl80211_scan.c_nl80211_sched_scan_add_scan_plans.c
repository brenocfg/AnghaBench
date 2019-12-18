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
struct wpa_driver_scan_params {unsigned int sched_scan_plans_num; struct sched_scan_plan* sched_scan_plans; } ;
struct TYPE_2__ {scalar_t__ max_sched_scan_plan_interval; scalar_t__ max_sched_scan_plan_iterations; } ;
struct wpa_driver_nl80211_data {TYPE_1__ capa; } ;
struct sched_scan_plan {scalar_t__ interval; scalar_t__ iterations; } ;
struct nlattr {int dummy; } ;
struct nl_msg {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 unsigned int NL80211_ATTR_SCHED_SCAN_PLANS ; 
 int /*<<< orphan*/  NL80211_SCHED_SCAN_PLAN_INTERVAL ; 
 int /*<<< orphan*/  NL80211_SCHED_SCAN_PLAN_ITERATIONS ; 
 int /*<<< orphan*/  nla_nest_end (struct nl_msg*,struct nlattr*) ; 
 struct nlattr* nla_nest_start (struct nl_msg*,unsigned int) ; 
 scalar_t__ nla_put_u32 (struct nl_msg*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static int
nl80211_sched_scan_add_scan_plans(struct wpa_driver_nl80211_data *drv,
				  struct nl_msg *msg,
				  struct wpa_driver_scan_params *params)
{
	struct nlattr *plans;
	struct sched_scan_plan *scan_plans = params->sched_scan_plans;
	unsigned int i;

	plans = nla_nest_start(msg, NL80211_ATTR_SCHED_SCAN_PLANS);
	if (!plans)
		return -1;

	for (i = 0; i < params->sched_scan_plans_num; i++) {
		struct nlattr *plan = nla_nest_start(msg, i + 1);

		if (!plan)
			return -1;

		if (!scan_plans[i].interval ||
		    scan_plans[i].interval >
		    drv->capa.max_sched_scan_plan_interval) {
			wpa_printf(MSG_DEBUG,
				   "nl80211: sched scan plan no. %u: Invalid interval: %u",
				   i, scan_plans[i].interval);
			return -1;
		}

		if (nla_put_u32(msg, NL80211_SCHED_SCAN_PLAN_INTERVAL,
				scan_plans[i].interval))
			return -1;

		if (scan_plans[i].iterations >
		    drv->capa.max_sched_scan_plan_iterations) {
			wpa_printf(MSG_DEBUG,
				   "nl80211: sched scan plan no. %u: Invalid number of iterations: %u",
				   i, scan_plans[i].iterations);
			return -1;
		}

		if (scan_plans[i].iterations &&
		    nla_put_u32(msg, NL80211_SCHED_SCAN_PLAN_ITERATIONS,
				scan_plans[i].iterations))
			return -1;

		nla_nest_end(msg, plan);

		/*
		 * All the scan plans must specify the number of iterations
		 * except the last plan, which will run infinitely. So if the
		 * number of iterations is not specified, this ought to be the
		 * last scan plan.
		 */
		if (!scan_plans[i].iterations)
			break;
	}

	if (i != params->sched_scan_plans_num - 1) {
		wpa_printf(MSG_DEBUG,
			   "nl80211: All sched scan plans but the last must specify number of iterations");
		return -1;
	}

	nla_nest_end(msg, plans);
	return 0;
}