#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct pt_query_decoder {int consume_packet; int /*<<< orphan*/  ip; } ;
struct TYPE_11__ {int /*<<< orphan*/  ip; } ;
struct TYPE_10__ {int /*<<< orphan*/  ip; } ;
struct TYPE_9__ {int /*<<< orphan*/  ip; } ;
struct TYPE_8__ {int /*<<< orphan*/  ip; int /*<<< orphan*/  aborted; } ;
struct TYPE_7__ {int /*<<< orphan*/  ip; } ;
struct TYPE_12__ {TYPE_5__ ptwrite; TYPE_4__ mwait; TYPE_3__ exstop; TYPE_2__ tsx; TYPE_1__ overflow; } ;
struct pt_event {int type; TYPE_6__ variant; } ;

/* Variables and functions */
 int pt_last_ip_query (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int pt_qry_event_ip (int /*<<< orphan*/ *,struct pt_event*,struct pt_query_decoder*) ; 
 int pte_internal ; 
#define  ptev_exstop 132 
#define  ptev_mwait 131 
#define  ptev_overflow 130 
#define  ptev_ptwrite 129 
#define  ptev_tsx 128 

__attribute__((used)) static int pt_qry_event_fup(struct pt_event *ev,
			    struct pt_query_decoder *decoder)
{
	if (!ev || !decoder)
		return -pte_internal;

	switch (ev->type) {
	case ptev_overflow:
		decoder->consume_packet = 1;

		/* We can't afford having a suppressed IP here. */
		return pt_last_ip_query(&ev->variant.overflow.ip,
					&decoder->ip);

	case ptev_tsx:
		if (!(ev->variant.tsx.aborted))
			decoder->consume_packet = 1;

		return pt_qry_event_ip(&ev->variant.tsx.ip, ev, decoder);

	case ptev_exstop:
		decoder->consume_packet = 1;

		return pt_qry_event_ip(&ev->variant.exstop.ip, ev, decoder);

	case ptev_mwait:
		decoder->consume_packet = 1;

		return pt_qry_event_ip(&ev->variant.mwait.ip, ev, decoder);

	case ptev_ptwrite:
		decoder->consume_packet = 1;

		return pt_qry_event_ip(&ev->variant.ptwrite.ip, ev, decoder);

	default:
		break;
	}

	return -pte_internal;
}