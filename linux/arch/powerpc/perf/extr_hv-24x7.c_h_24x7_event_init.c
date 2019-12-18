#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_6__ {int /*<<< orphan*/  prev_count; } ;
struct TYPE_5__ {scalar_t__ type; int /*<<< orphan*/  config2; int /*<<< orphan*/  config1; int /*<<< orphan*/  config; } ;
struct perf_event {TYPE_3__ hw; TYPE_2__ attr; TYPE_1__* pmu; } ;
struct hv_perf_caps {int /*<<< orphan*/  collect_privileged; } ;
struct TYPE_4__ {scalar_t__ type; } ;

/* Variables and functions */
 int EACCES ; 
 int EINVAL ; 
 int EIO ; 
 int ENOENT ; 
 int EOPNOTSUPP ; 
 unsigned int HV_PERF_DOMAIN_MAX ; 
 unsigned int event_get_domain (struct perf_event*) ; 
 scalar_t__ event_get_lpar (struct perf_event*) ; 
 scalar_t__ event_get_lpar_max () ; 
 int event_get_offset (struct perf_event*) ; 
 scalar_t__ event_get_reserved1 (struct perf_event*) ; 
 scalar_t__ event_get_reserved2 (struct perf_event*) ; 
 scalar_t__ event_get_reserved3 (struct perf_event*) ; 
 scalar_t__ has_branch_stack (struct perf_event*) ; 
 unsigned long hv_perf_caps_get (struct hv_perf_caps*) ; 
 int /*<<< orphan*/  is_physical_domain (unsigned int) ; 
 int /*<<< orphan*/  local64_xchg (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_devel (char*,...) ; 
 scalar_t__ single_24x7_request (struct perf_event*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int h_24x7_event_init(struct perf_event *event)
{
	struct hv_perf_caps caps;
	unsigned domain;
	unsigned long hret;
	u64 ct;

	/* Not our event */
	if (event->attr.type != event->pmu->type)
		return -ENOENT;

	/* Unused areas must be 0 */
	if (event_get_reserved1(event) ||
	    event_get_reserved2(event) ||
	    event_get_reserved3(event)) {
		pr_devel("reserved set when forbidden 0x%llx(0x%llx) 0x%llx(0x%llx) 0x%llx(0x%llx)\n",
				event->attr.config,
				event_get_reserved1(event),
				event->attr.config1,
				event_get_reserved2(event),
				event->attr.config2,
				event_get_reserved3(event));
		return -EINVAL;
	}

	/* no branch sampling */
	if (has_branch_stack(event))
		return -EOPNOTSUPP;

	/* offset must be 8 byte aligned */
	if (event_get_offset(event) % 8) {
		pr_devel("bad alignment\n");
		return -EINVAL;
	}

	domain = event_get_domain(event);
	if (domain >= HV_PERF_DOMAIN_MAX) {
		pr_devel("invalid domain %d\n", domain);
		return -EINVAL;
	}

	hret = hv_perf_caps_get(&caps);
	if (hret) {
		pr_devel("could not get capabilities: rc=%ld\n", hret);
		return -EIO;
	}

	/* Physical domains & other lpars require extra capabilities */
	if (!caps.collect_privileged && (is_physical_domain(domain) ||
		(event_get_lpar(event) != event_get_lpar_max()))) {
		pr_devel("hv permissions disallow: is_physical_domain:%d, lpar=0x%llx\n",
				is_physical_domain(domain),
				event_get_lpar(event));
		return -EACCES;
	}

	/* Get the initial value of the counter for this event */
	if (single_24x7_request(event, &ct)) {
		pr_devel("test hcall failed\n");
		return -EIO;
	}
	(void)local64_xchg(&event->hw.prev_count, ct);

	return 0;
}