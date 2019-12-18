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
struct perf_event {int dummy; } ;
struct intel_uncore_box {int dummy; } ;
struct event_constraint {int dummy; } ;

/* Variables and functions */
 struct event_constraint* __snbep_cbox_get_constraint (struct intel_uncore_box*,struct perf_event*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snbep_cbox_filter_mask ; 

__attribute__((used)) static struct event_constraint *
snbep_cbox_get_constraint(struct intel_uncore_box *box, struct perf_event *event)
{
	return __snbep_cbox_get_constraint(box, event, snbep_cbox_filter_mask);
}