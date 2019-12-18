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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_4__ {scalar_t__ type; scalar_t__ config2; } ;
struct perf_event {TYPE_2__ attr; TYPE_1__* pmu; } ;
struct TYPE_3__ {scalar_t__ type; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
 int EOPNOTSUPP ; 
 scalar_t__ HGPCI_MAX_DATA_BYTES ; 
 int /*<<< orphan*/  event_get_counter_info_version (struct perf_event*) ; 
 int event_get_length (struct perf_event*) ; 
 scalar_t__ event_get_offset (struct perf_event*) ; 
 int /*<<< orphan*/  event_get_request (struct perf_event*) ; 
 int /*<<< orphan*/  event_get_secondary_index (struct perf_event*) ; 
 int /*<<< orphan*/  event_get_starting_index (struct perf_event*) ; 
 scalar_t__ has_branch_stack (struct perf_event*) ; 
 int /*<<< orphan*/  pr_devel (char*,...) ; 
 scalar_t__ single_gpci_request (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int h_gpci_event_init(struct perf_event *event)
{
	u64 count;
	u8 length;

	/* Not our event */
	if (event->attr.type != event->pmu->type)
		return -ENOENT;

	/* config2 is unused */
	if (event->attr.config2) {
		pr_devel("config2 set when reserved\n");
		return -EINVAL;
	}

	/* no branch sampling */
	if (has_branch_stack(event))
		return -EOPNOTSUPP;

	length = event_get_length(event);
	if (length < 1 || length > 8) {
		pr_devel("length invalid\n");
		return -EINVAL;
	}

	/* last byte within the buffer? */
	if ((event_get_offset(event) + length) > HGPCI_MAX_DATA_BYTES) {
		pr_devel("request outside of buffer: %zu > %zu\n",
				(size_t)event_get_offset(event) + length,
				HGPCI_MAX_DATA_BYTES);
		return -EINVAL;
	}

	/* check if the request works... */
	if (single_gpci_request(event_get_request(event),
				event_get_starting_index(event),
				event_get_secondary_index(event),
				event_get_counter_info_version(event),
				event_get_offset(event),
				length,
				&count)) {
		pr_devel("gpci hcall failed\n");
		return -EINVAL;
	}

	return 0;
}