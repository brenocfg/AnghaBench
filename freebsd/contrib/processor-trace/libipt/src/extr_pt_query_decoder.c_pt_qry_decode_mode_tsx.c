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
struct pt_query_decoder {int /*<<< orphan*/  evq; struct pt_event* event; int /*<<< orphan*/  enabled; } ;
struct pt_packet_mode_tsx {int /*<<< orphan*/  abrt; int /*<<< orphan*/  intx; } ;
struct TYPE_3__ {int /*<<< orphan*/  aborted; int /*<<< orphan*/  speculative; scalar_t__ ip; } ;
struct TYPE_4__ {TYPE_1__ tsx; } ;
struct pt_event {int ip_suppressed; TYPE_2__ variant; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  evb_fup ; 
 struct pt_event* pt_evq_enqueue (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct pt_event* pt_evq_standalone (int /*<<< orphan*/ *) ; 
 int pt_qry_event_time (struct pt_event*,struct pt_query_decoder*) ; 
 int pte_internal ; 
 int pte_nomem ; 
 int /*<<< orphan*/  ptev_tsx ; 

__attribute__((used)) static int pt_qry_decode_mode_tsx(struct pt_query_decoder *decoder,
				  const struct pt_packet_mode_tsx *packet)
{
	struct pt_event *event;

	if (!decoder || !packet)
		return -pte_internal;

	/* MODE.TSX is standalone if tracing is disabled. */
	if (!decoder->enabled) {
		event = pt_evq_standalone(&decoder->evq);
		if (!event)
			return -pte_internal;

		/* We don't have an IP in this case. */
		event->variant.tsx.ip = 0;
		event->ip_suppressed = 1;

		/* Publish the event. */
		decoder->event = event;
	} else {
		/* MODE.TSX binds to FUP. */
		event = pt_evq_enqueue(&decoder->evq, evb_fup);
		if (!event)
			return -pte_nomem;
	}

	event->type = ptev_tsx;
	event->variant.tsx.speculative = packet->intx;
	event->variant.tsx.aborted = packet->abrt;

	return pt_qry_event_time(event, decoder);
}