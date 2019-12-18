#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
struct pt_time_cal {int dummy; } ;
struct pt_time {int dummy; } ;
struct pt_last_ip {int dummy; } ;
struct TYPE_6__ {scalar_t__ begin; } ;
struct pt_query_decoder {int enabled; struct pt_event* event; struct pt_time_cal tcal; struct pt_time time; struct pt_last_ip ip; TYPE_3__ config; scalar_t__ pos; int /*<<< orphan*/  evq; } ;
struct pt_packet_ip {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  ip; } ;
struct TYPE_5__ {TYPE_1__ overflow; } ;
struct pt_event {TYPE_2__ variant; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 struct pt_event* pt_evq_standalone (int /*<<< orphan*/ *) ; 
 int pt_last_ip_query (int /*<<< orphan*/ *,struct pt_last_ip*) ; 
 int pt_last_ip_update_ip (struct pt_last_ip*,struct pt_packet_ip const*,TYPE_3__*) ; 
 int pt_qry_event_time (struct pt_event*,struct pt_query_decoder*) ; 
 int pte_bad_context ; 
 int pte_internal ; 
 int /*<<< orphan*/  ptev_overflow ; 

__attribute__((used)) static int skd010_recover(struct pt_query_decoder *decoder,
			  const struct pt_packet_ip *packet,
			  const struct pt_time_cal *tcal,
			  const struct pt_time *time, uint64_t offset)
{
	struct pt_last_ip ip;
	struct pt_event *ev;
	int errcode;

	if (!decoder || !packet || !tcal || !time)
		return -pte_internal;

	/* We use the decoder's IP.  It should be newly initialized. */
	ip = decoder->ip;

	/* Extract the IP payload from the packet. */
	errcode = pt_last_ip_update_ip(&ip, packet, &decoder->config);
	if (errcode < 0)
		return errcode;

	/* Synthesize the overflow event. */
	ev = pt_evq_standalone(&decoder->evq);
	if (!ev)
		return -pte_internal;

	ev->type = ptev_overflow;

	/* We do need a full IP. */
	errcode = pt_last_ip_query(&ev->variant.overflow.ip, &ip);
	if (errcode < 0)
		return -pte_bad_context;

	/* We continue decoding at the given offset. */
	decoder->pos = decoder->config.begin + offset;

	/* Tracing is enabled. */
	decoder->enabled = 1;
	decoder->ip = ip;

	decoder->time = *time;
	decoder->tcal = *tcal;

	/* Publish the event. */
	decoder->event = ev;

	return pt_qry_event_time(ev, decoder);
}