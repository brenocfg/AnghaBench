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
typedef  scalar_t__ uint8_t ;
struct pt_event_queue {scalar_t__* begin; scalar_t__* end; } ;
typedef  enum pt_event_binding { ____Placeholder_pt_event_binding } pt_event_binding ;

/* Variables and functions */
 int evb_max ; 
 scalar_t__ evq_max ; 
 int pte_internal ; 

int pt_evq_empty(const struct pt_event_queue *evq, enum pt_event_binding evb)
{
	uint8_t begin, end;

	if (!evq)
		return -pte_internal;

	if (evb_max <= evb)
		return -pte_internal;

	begin = evq->begin[evb];
	end = evq->end[evb];

	if (evq_max <= begin)
		return -pte_internal;

	if (evq_max <= end)
		return -pte_internal;

	return begin == end;
}