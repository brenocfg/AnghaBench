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
struct pt_query_decoder {int pos; struct pt_event* event; int /*<<< orphan*/  evq; int /*<<< orphan*/  config; } ;
struct pt_packet_pwrx {scalar_t__ autonomous; scalar_t__ store; scalar_t__ interrupt; int /*<<< orphan*/  deepest; int /*<<< orphan*/  last; } ;
struct TYPE_3__ {int interrupt; int store; int autonomous; int /*<<< orphan*/  deepest; int /*<<< orphan*/  last; } ;
struct TYPE_4__ {TYPE_1__ pwrx; } ;
struct pt_event {TYPE_2__ variant; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 struct pt_event* pt_evq_standalone (int /*<<< orphan*/ *) ; 
 int pt_pkt_read_pwrx (struct pt_packet_pwrx*,int,int /*<<< orphan*/ *) ; 
 int pte_internal ; 
 int /*<<< orphan*/  ptev_pwrx ; 

int pt_qry_decode_pwrx(struct pt_query_decoder *decoder)
{
	struct pt_packet_pwrx packet;
	struct pt_event *event;
	int size;

	if (!decoder)
		return -pte_internal;

	size = pt_pkt_read_pwrx(&packet, decoder->pos, &decoder->config);
	if (size < 0)
		return size;

	event = pt_evq_standalone(&decoder->evq);
	if (!event)
		return -pte_internal;

	event->type = ptev_pwrx;
	event->variant.pwrx.last = packet.last;
	event->variant.pwrx.deepest = packet.deepest;

	if (packet.interrupt)
		event->variant.pwrx.interrupt = 1;
	if (packet.store)
		event->variant.pwrx.store = 1;
	if (packet.autonomous)
		event->variant.pwrx.autonomous = 1;

	decoder->event = event;

	decoder->pos += size;
	return 0;
}