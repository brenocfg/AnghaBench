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
typedef  int /*<<< orphan*/  uint64_t ;
struct pt_query_decoder {int /*<<< orphan*/  evq; int /*<<< orphan*/  ip; scalar_t__ consume_packet; struct pt_event* event; } ;
struct TYPE_3__ {int /*<<< orphan*/  from; } ;
struct TYPE_4__ {TYPE_1__ async_branch; } ;
struct pt_event {TYPE_2__ variant; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  evb_fup ; 
 int /*<<< orphan*/  evb_tip ; 
 struct pt_event* pt_evq_dequeue (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct pt_event* pt_evq_enqueue (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ pt_evq_pending (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int pt_last_ip_query (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int pt_qry_consume_fup (struct pt_query_decoder*,int) ; 
 int pt_qry_decode_ip (struct pt_query_decoder*) ; 
 int pt_qry_event_fup (struct pt_event*,struct pt_query_decoder*) ; 
 int pt_qry_event_time (struct pt_event*,struct pt_query_decoder*) ; 
 int pte_internal ; 
 int pte_nomem ; 
 int /*<<< orphan*/  ptev_async_branch ; 

int pt_qry_decode_fup(struct pt_query_decoder *decoder)
{
	struct pt_event *ev;
	int size, errcode;

	if (!decoder)
		return -pte_internal;

	size = pt_qry_decode_ip(decoder);
	if (size < 0)
		return size;

	/* Process any pending events binding to FUP. */
	ev = pt_evq_dequeue(&decoder->evq, evb_fup);
	if (ev) {
		errcode = pt_qry_event_fup(ev, decoder);
		if (errcode < 0)
			return errcode;

		/* Publish the event. */
		decoder->event = ev;

		/* Process further pending events. */
		if (pt_evq_pending(&decoder->evq, evb_fup))
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
	} else {
		/* FUP indicates an async branch event; it binds to TIP.
		 *
		 * We do need an IP in this case.
		 */
		uint64_t ip;

		errcode = pt_last_ip_query(&ip, &decoder->ip);
		if (errcode < 0)
			return errcode;

		ev = pt_evq_enqueue(&decoder->evq, evb_tip);
		if (!ev)
			return -pte_nomem;

		ev->type = ptev_async_branch;
		ev->variant.async_branch.from = ip;

		errcode = pt_qry_event_time(ev, decoder);
		if (errcode < 0)
			return errcode;
	}

	return pt_qry_consume_fup(decoder, size);
}