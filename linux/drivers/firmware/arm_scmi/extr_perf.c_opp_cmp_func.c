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
struct scmi_opp {int perf; } ;

/* Variables and functions */

__attribute__((used)) static int opp_cmp_func(const void *opp1, const void *opp2)
{
	const struct scmi_opp *t1 = opp1, *t2 = opp2;

	return t1->perf - t2->perf;
}