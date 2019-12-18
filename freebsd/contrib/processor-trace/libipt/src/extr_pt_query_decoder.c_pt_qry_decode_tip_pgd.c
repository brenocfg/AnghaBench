#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct pt_query_decoder {int /*<<< orphan*/  evq; struct pt_event* event; } ;
struct TYPE_3__ {int /*<<< orphan*/  ip; } ;
struct TYPE_4__ {TYPE_1__ disabled; } ;
struct pt_event {TYPE_2__ variant; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  evb_tip ; 
 struct pt_event* pt_evq_dequeue (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ pt_evq_pending (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct pt_event* pt_evq_standalone (int /*<<< orphan*/ *) ; 
 int pt_qry_consume_tip_pgd (struct pt_query_decoder*,int) ; 
 int pt_qry_decode_ip (struct pt_query_decoder*) ; 
 int pt_qry_event_ip (int /*<<< orphan*/ *,struct pt_event*,struct pt_query_decoder*) ; 
 int pt_qry_event_time (struct pt_event*,struct pt_query_decoder*) ; 
 int pt_qry_event_tip_pgd (struct pt_event*,struct pt_query_decoder*) ; 
 int pte_internal ; 
 int /*<<< orphan*/  ptev_disabled ; 

int pt_qry_decode_tip_pgd(struct pt_query_decoder *decoder)
{
	struct pt_event *ev;
	int size, errcode;

	if (!decoder)
		return -pte_internal;

	size = pt_qry_decode_ip(decoder);
	if (size < 0)
		return size;

	/* Process any pending events binding to TIP. */
	ev = pt_evq_dequeue(&decoder->evq, evb_tip);
	if (ev) {
		errcode = pt_qry_event_tip_pgd(ev, decoder);
		if (errcode < 0)
			return errcode;
	} else {
		/* This packet signals a standalone disabled event. */
		ev = pt_evq_standalone(&decoder->evq);
		if (!ev)
			return -pte_internal;
		ev->type = ptev_disabled;

		errcode = pt_qry_event_ip(&ev->variant.disabled.ip, ev,
					  decoder);
		if (errcode < 0)
			return errcode;

		errcode = pt_qry_event_time(ev, decoder);
		if (errcode < 0)
			return errcode;
	}

	/* We must have an event. Either the initial enable event or one of the
	 * queued events.
	 */
	if (!ev)
		return -pte_internal;

	/* Publish the event. */
	decoder->event = ev;

	/* Process further pending events. */
	if (pt_evq_pending(&decoder->evq, evb_tip))
		return 0;

	return pt_qry_consume_tip_pgd(decoder, size);
}