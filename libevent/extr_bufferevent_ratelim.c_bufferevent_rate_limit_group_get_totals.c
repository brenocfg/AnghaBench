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
struct bufferevent_rate_limit_group {int /*<<< orphan*/  total_written; int /*<<< orphan*/  total_read; } ;
typedef  int /*<<< orphan*/  ev_uint64_t ;

/* Variables and functions */
 int /*<<< orphan*/  EVUTIL_ASSERT (int /*<<< orphan*/ ) ; 

void
bufferevent_rate_limit_group_get_totals(struct bufferevent_rate_limit_group *grp,
    ev_uint64_t *total_read_out, ev_uint64_t *total_written_out)
{
	EVUTIL_ASSERT(grp != NULL);
	if (total_read_out)
		*total_read_out = grp->total_read;
	if (total_written_out)
		*total_written_out = grp->total_written;
}