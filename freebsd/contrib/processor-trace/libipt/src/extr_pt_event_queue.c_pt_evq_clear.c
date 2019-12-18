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
struct pt_event_queue {scalar_t__* end; scalar_t__* begin; } ;
typedef  enum pt_event_binding { ____Placeholder_pt_event_binding } pt_event_binding ;

/* Variables and functions */
 int evb_max ; 
 int pte_internal ; 

int pt_evq_clear(struct pt_event_queue *evq, enum pt_event_binding evb)
{
	if (!evq)
		return -pte_internal;

	if (evb_max <= evb)
		return -pte_internal;

	evq->begin[evb] = 0;
	evq->end[evb] = 0;

	return 0;
}