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
struct pt_event_queue {scalar_t__* begin; scalar_t__* end; struct pt_event** queue; } ;
struct pt_event {int dummy; } ;
typedef  enum pt_event_binding { ____Placeholder_pt_event_binding } pt_event_binding ;

/* Variables and functions */
 int evb_max ; 
 scalar_t__ evq_max ; 
 scalar_t__ pt_evq_inc (scalar_t__) ; 

struct pt_event *pt_evq_dequeue(struct pt_event_queue *evq,
				enum pt_event_binding evb)
{
	uint8_t begin, end;

	if (!evq)
		return NULL;

	if (evb_max <= evb)
		return NULL;

	begin = evq->begin[evb];
	end = evq->end[evb];

	if (evq_max <= begin)
		return NULL;

	if (evq_max <= end)
		return NULL;

	if (begin == end)
		return NULL;

	evq->begin[evb] = pt_evq_inc(begin);

	return &evq->queue[evb][begin];
}