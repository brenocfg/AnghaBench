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
struct delegpt_ns {int /*<<< orphan*/  resolved; struct delegpt_ns* next; } ;
struct delegpt {struct delegpt_ns* nslist; } ;

/* Variables and functions */

void
delegpt_count_ns(struct delegpt* dp, size_t* numns, size_t* missing)
{
	struct delegpt_ns* ns;
	*numns = 0;
	*missing = 0;
	for(ns = dp->nslist; ns; ns = ns->next) {
		(*numns)++;
		if(!ns->resolved)
			(*missing)++;
	}
}