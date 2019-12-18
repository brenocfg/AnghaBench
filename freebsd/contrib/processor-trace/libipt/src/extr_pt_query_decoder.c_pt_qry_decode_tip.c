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
struct pt_query_decoder {scalar_t__ consume_packet; int /*<<< orphan*/  evq; struct pt_event* event; } ;
struct pt_event {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  evb_tip ; 
 struct pt_event* pt_evq_dequeue (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ pt_evq_pending (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int pt_qry_consume_tip (struct pt_query_decoder*,int) ; 
 int pt_qry_decode_ip (struct pt_query_decoder*) ; 
 int pt_qry_event_tip (struct pt_event*,struct pt_query_decoder*) ; 
 int pte_internal ; 

int pt_qry_decode_tip(struct pt_query_decoder *decoder)
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
		errcode = pt_qry_event_tip(ev, decoder);
		if (errcode < 0)
			return errcode;

		/* Publish the event. */
		decoder->event = ev;

		/* Process further pending events. */
		if (pt_evq_pending(&decoder->evq, evb_tip))
			return 0;

		/* No further events.
		 *
		 * If none of the events consumed the packet, we're done.
		 */
		if (!decoder->consume_packet)
			return 0;

		/* We're done with this packet. Clear the flag we set previously
		 * and consume it.
		 */
		decoder->consume_packet = 0;
	}

	return pt_qry_consume_tip(decoder, size);
}