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
struct wpa_supplicant {unsigned int sched_scan_plans_num; unsigned int max_sched_scan_plans; struct sched_scan_plan* sched_scan_plans; scalar_t__ max_sched_scan_plan_iterations; int /*<<< orphan*/  max_sched_scan_plan_interval; } ;
struct sched_scan_plan {int /*<<< orphan*/  interval; scalar_t__ iterations; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_ERROR ; 
 int /*<<< orphan*/  MSG_WARNING ; 
 char* cstr_token (char const*,char*,char const**) ; 
 int /*<<< orphan*/  os_free (struct sched_scan_plan*) ; 
 int /*<<< orphan*/  os_memcpy (struct sched_scan_plan*,struct sched_scan_plan*,int) ; 
 struct sched_scan_plan* os_realloc_array (struct sched_scan_plan*,unsigned int,int) ; 
 int sscanf (char const*,char*,int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 

int wpas_sched_scan_plans_set(struct wpa_supplicant *wpa_s, const char *cmd)
{
	struct sched_scan_plan *scan_plans = NULL;
	const char *token, *context = NULL;
	unsigned int num = 0;

	if (!cmd)
		return -1;

	if (!cmd[0]) {
		wpa_printf(MSG_DEBUG, "Clear sched scan plans");
		os_free(wpa_s->sched_scan_plans);
		wpa_s->sched_scan_plans = NULL;
		wpa_s->sched_scan_plans_num = 0;
		return 0;
	}

	while ((token = cstr_token(cmd, " ", &context))) {
		int ret;
		struct sched_scan_plan *scan_plan, *n;

		n = os_realloc_array(scan_plans, num + 1, sizeof(*scan_plans));
		if (!n)
			goto fail;

		scan_plans = n;
		scan_plan = &scan_plans[num];
		num++;

		ret = sscanf(token, "%u:%u", &scan_plan->interval,
			     &scan_plan->iterations);
		if (ret <= 0 || ret > 2 || !scan_plan->interval) {
			wpa_printf(MSG_ERROR,
				   "Invalid sched scan plan input: %s", token);
			goto fail;
		}

		if (scan_plan->interval > wpa_s->max_sched_scan_plan_interval) {
			wpa_printf(MSG_WARNING,
				   "scan plan %u: Scan interval too long(%u), use the maximum allowed(%u)",
				   num, scan_plan->interval,
				   wpa_s->max_sched_scan_plan_interval);
			scan_plan->interval =
				wpa_s->max_sched_scan_plan_interval;
		}

		if (ret == 1) {
			scan_plan->iterations = 0;
			break;
		}

		if (!scan_plan->iterations) {
			wpa_printf(MSG_ERROR,
				   "scan plan %u: Number of iterations cannot be zero",
				   num);
			goto fail;
		}

		if (scan_plan->iterations >
		    wpa_s->max_sched_scan_plan_iterations) {
			wpa_printf(MSG_WARNING,
				   "scan plan %u: Too many iterations(%u), use the maximum allowed(%u)",
				   num, scan_plan->iterations,
				   wpa_s->max_sched_scan_plan_iterations);
			scan_plan->iterations =
				wpa_s->max_sched_scan_plan_iterations;
		}

		wpa_printf(MSG_DEBUG,
			   "scan plan %u: interval=%u iterations=%u",
			   num, scan_plan->interval, scan_plan->iterations);
	}

	if (!scan_plans) {
		wpa_printf(MSG_ERROR, "Invalid scan plans entry");
		goto fail;
	}

	if (cstr_token(cmd, " ", &context) || scan_plans[num - 1].iterations) {
		wpa_printf(MSG_ERROR,
			   "All scan plans but the last must specify a number of iterations");
		goto fail;
	}

	wpa_printf(MSG_DEBUG, "scan plan %u (last plan): interval=%u",
		   num, scan_plans[num - 1].interval);

	if (num > wpa_s->max_sched_scan_plans) {
		wpa_printf(MSG_WARNING,
			   "Too many scheduled scan plans (only %u supported)",
			   wpa_s->max_sched_scan_plans);
		wpa_printf(MSG_WARNING,
			   "Use only the first %u scan plans, and the last one (in infinite loop)",
			   wpa_s->max_sched_scan_plans - 1);
		os_memcpy(&scan_plans[wpa_s->max_sched_scan_plans - 1],
			  &scan_plans[num - 1], sizeof(*scan_plans));
		num = wpa_s->max_sched_scan_plans;
	}

	os_free(wpa_s->sched_scan_plans);
	wpa_s->sched_scan_plans = scan_plans;
	wpa_s->sched_scan_plans_num = num;

	return 0;

fail:
	os_free(scan_plans);
	wpa_printf(MSG_ERROR, "invalid scan plans list");
	return -1;
}