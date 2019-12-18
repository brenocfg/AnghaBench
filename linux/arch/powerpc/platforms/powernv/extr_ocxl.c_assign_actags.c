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
typedef  scalar_t__ u16 ;
struct npu_link {int assignment_done; scalar_t__* fn_desired_actags; TYPE_1__* fn_actags; int /*<<< orphan*/  dev; int /*<<< orphan*/  bus; int /*<<< orphan*/  domain; } ;
struct TYPE_2__ {scalar_t__ count; scalar_t__ start; } ;

/* Variables and functions */
 scalar_t__ PNV_OCXL_ACTAG_MAX ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 scalar_t__ assign_fn_actags (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,scalar_t__,scalar_t__,scalar_t__) ; 

__attribute__((used)) static void assign_actags(struct npu_link *link)
{
	u16 actag_count, range_start = 0, total_desired = 0;
	int i;

	for (i = 0; i < 8; i++)
		total_desired += link->fn_desired_actags[i];

	for (i = 0; i < 8; i++) {
		if (link->fn_desired_actags[i]) {
			actag_count = assign_fn_actags(
				link->fn_desired_actags[i],
				total_desired);
			link->fn_actags[i].start = range_start;
			link->fn_actags[i].count = actag_count;
			range_start += actag_count;
			WARN_ON(range_start >= PNV_OCXL_ACTAG_MAX);
		}
		pr_debug("link %x:%x:%x fct %d actags: start=%d count=%d (desired=%d)\n",
			link->domain, link->bus, link->dev, i,
			link->fn_actags[i].start, link->fn_actags[i].count,
			link->fn_desired_actags[i]);
	}
	link->assignment_done = true;
}