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
struct pt_query_decoder {int consume_packet; int enabled; int /*<<< orphan*/  evq; struct pt_event* event; int /*<<< orphan*/  tnt; int /*<<< orphan*/  ip; } ;
struct TYPE_3__ {int /*<<< orphan*/  ip; } ;
struct TYPE_4__ {TYPE_1__ enabled; } ;
struct pt_event {TYPE_2__ variant; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  evb_tip ; 
 struct pt_event* pt_evq_dequeue (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ pt_evq_pending (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct pt_event* pt_evq_standalone (int /*<<< orphan*/ *) ; 
 int pt_last_ip_query (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int pt_qry_consume_tip_pge (struct pt_query_decoder*,int) ; 
 int pt_qry_decode_ip (struct pt_query_decoder*) ; 
 int pt_qry_event_time (struct pt_event*,struct pt_query_decoder*) ; 
 int pt_qry_event_tip_pge (struct pt_event*,struct pt_query_decoder*) ; 
 int /*<<< orphan*/  pt_tnt_cache_init (int /*<<< orphan*/ *) ; 
 int pte_bad_packet ; 
 int pte_internal ; 
 int /*<<< orphan*/  ptev_enabled ; 

int pt_qry_decode_tip_pge(struct pt_query_decoder *decoder)
{
	struct pt_event *ev;
	int size, errcode;

	if (!decoder)
		return -pte_internal;

	size = pt_qry_decode_ip(decoder);
	if (size < 0)
		return size;

	/* We send the enable event first. This is more convenient for our users
	 * and does not require them to either store or blindly apply other
	 * events that might be pending.
	 *
	 * We use the consume packet decoder flag to indicate this.
	 */
	if (!decoder->consume_packet) {
		/* This packet signals a standalone enabled event. */
		ev = pt_evq_standalone(&decoder->evq);
		if (!ev)
			return -pte_internal;

		ev->type = ptev_enabled;

		/* We can't afford having a suppressed IP here. */
		errcode = pt_last_ip_query(&ev->variant.enabled.ip,
					   &decoder->ip);
		if (errcode < 0)
			return -pte_bad_packet;

		errcode = pt_qry_event_time(ev, decoder);
		if (errcode < 0)
			return errcode;

		/* Discard any cached TNT bits.
		 *
		 * They should have been consumed at the corresponding disable
		 * event. If they have not, for whatever reason, discard them
		 * now so our user does not get out of sync.
		 */
		pt_tnt_cache_init(&decoder->tnt);

		/* Process pending events next. */
		decoder->consume_packet = 1;
		decoder->enabled = 1;
	} else {
		/* Process any pending events binding to TIP. */
		ev = pt_evq_dequeue(&decoder->evq, evb_tip);
		if (ev) {
			errcode = pt_qry_event_tip_pge(ev, decoder);
			if (errcode < 0)
				return errcode;
		}
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

	/* We must consume the packet. */
	if (!decoder->consume_packet)
		return -pte_internal;

	decoder->consume_packet = 0;

	return pt_qry_consume_tip_pge(decoder, size);
}