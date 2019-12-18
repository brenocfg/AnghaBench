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
struct pt_query_decoder {int /*<<< orphan*/  time; } ;
struct pt_event {int has_tsc; int /*<<< orphan*/  lost_cyc; int /*<<< orphan*/  lost_mtc; int /*<<< orphan*/  tsc; } ;

/* Variables and functions */
 int pt_time_query_tsc (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int pte_internal ; 
 int pte_no_time ; 

__attribute__((used)) static int pt_qry_event_time(struct pt_event *event,
			     const struct pt_query_decoder *decoder)
{
	int errcode;

	if (!event || !decoder)
		return -pte_internal;

	errcode = pt_time_query_tsc(&event->tsc, &event->lost_mtc,
				    &event->lost_cyc, &decoder->time);
	if (errcode < 0) {
		if (errcode != -pte_no_time)
			return errcode;
	} else
		event->has_tsc = 1;

	return 0;
}