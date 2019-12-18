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
struct pt_query_decoder {int /*<<< orphan*/  evq; } ;
struct pt_packet_mode_exec {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  mode; } ;
struct TYPE_4__ {TYPE_1__ exec_mode; } ;
struct pt_event {TYPE_2__ variant; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  evb_tip ; 
 struct pt_event* pt_evq_enqueue (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pt_get_exec_mode (struct pt_packet_mode_exec const*) ; 
 int pt_qry_event_time (struct pt_event*,struct pt_query_decoder*) ; 
 int pte_internal ; 
 int pte_nomem ; 
 int /*<<< orphan*/  ptev_exec_mode ; 

__attribute__((used)) static int pt_qry_decode_mode_exec(struct pt_query_decoder *decoder,
				   const struct pt_packet_mode_exec *packet)
{
	struct pt_event *event;

	if (!decoder || !packet)
		return -pte_internal;

	/* MODE.EXEC binds to TIP. */
	event = pt_evq_enqueue(&decoder->evq, evb_tip);
	if (!event)
		return -pte_nomem;

	event->type = ptev_exec_mode;
	event->variant.exec_mode.mode = pt_get_exec_mode(packet);

	return pt_qry_event_time(event, decoder);
}