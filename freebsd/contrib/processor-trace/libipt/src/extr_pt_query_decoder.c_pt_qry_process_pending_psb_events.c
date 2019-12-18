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
struct pt_query_decoder {struct pt_event* event; int /*<<< orphan*/  evq; } ;
struct pt_event {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  evb_psbend ; 
 struct pt_event* pt_evq_dequeue (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int pt_qry_event_psbend (struct pt_event*,struct pt_query_decoder*) ; 
 int pte_internal ; 

__attribute__((used)) static int pt_qry_process_pending_psb_events(struct pt_query_decoder *decoder)
{
	struct pt_event *ev;
	int errcode;

	if (!decoder)
		return -pte_internal;

	ev = pt_evq_dequeue(&decoder->evq, evb_psbend);
	if (!ev)
		return 0;

	errcode = pt_qry_event_psbend(ev, decoder);
	if (errcode < 0)
		return errcode;

	/* Publish the event. */
	decoder->event = ev;

	/* Signal a pending event. */
	return 1;
}