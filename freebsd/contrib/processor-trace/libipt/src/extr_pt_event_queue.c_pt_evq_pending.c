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
struct pt_event_queue {int dummy; } ;
typedef  enum pt_event_binding { ____Placeholder_pt_event_binding } pt_event_binding ;

/* Variables and functions */
 int pt_evq_empty (struct pt_event_queue const*,int) ; 

int pt_evq_pending(const struct pt_event_queue *evq, enum pt_event_binding evb)
{
	int errcode;

	errcode = pt_evq_empty(evq, evb);
	if (errcode < 0)
		return errcode;

	return !errcode;
}