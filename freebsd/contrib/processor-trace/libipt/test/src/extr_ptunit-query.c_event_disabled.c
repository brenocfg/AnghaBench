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
typedef  int /*<<< orphan*/  uint64_t ;
struct ptunit_result {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  ip; } ;
struct pt_encoder {int dummy; } ;
struct pt_query_decoder {int dummy; } ;
struct ptu_decoder_fixture {TYPE_3__ last_ip; int /*<<< orphan*/  config; struct pt_encoder encoder; struct pt_query_decoder decoder; } ;
struct pt_packet_ip {int ipc; int /*<<< orphan*/  ip; } ;
struct TYPE_4__ {int /*<<< orphan*/  ip; } ;
struct TYPE_5__ {TYPE_1__ disabled; } ;
struct pt_event {int type; int has_tsc; int /*<<< orphan*/  tsc; TYPE_2__ variant; int /*<<< orphan*/  ip_suppressed; } ;
typedef  int /*<<< orphan*/  event ;
typedef  enum pt_ip_compression { ____Placeholder_pt_ip_compression } pt_ip_compression ;

/* Variables and functions */
 int /*<<< orphan*/  pt_dfix_sext_ip ; 
 int /*<<< orphan*/  pt_encode_tip_pgd (struct pt_encoder*,int /*<<< orphan*/ ,int) ; 
 int pt_ipc_suppressed ; 
 int /*<<< orphan*/  pt_last_ip_update_ip (TYPE_3__*,struct pt_packet_ip*,int /*<<< orphan*/ *) ; 
 int pt_qry_event (struct pt_query_decoder*,struct pt_event*,int) ; 
 int ptev_disabled ; 
 int pts_eos ; 
 int /*<<< orphan*/  ptu_check (int /*<<< orphan*/ ,struct pt_query_decoder*) ; 
 int /*<<< orphan*/  ptu_int_eq (int,int) ; 
 struct ptunit_result ptu_passed () ; 
 int /*<<< orphan*/  ptu_sync_decoder ; 
 int /*<<< orphan*/  ptu_uint_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ptu_uint_ne (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct ptunit_result event_disabled(struct ptu_decoder_fixture *dfix,
					   enum pt_ip_compression ipc,
					   uint64_t tsc)
{
	struct pt_query_decoder *decoder = &dfix->decoder;
	struct pt_encoder *encoder = &dfix->encoder;
	struct pt_packet_ip packet;
	struct pt_event event;
	int errcode;

	packet.ipc = ipc;
	packet.ip = pt_dfix_sext_ip;
	pt_last_ip_update_ip(&dfix->last_ip, &packet, &dfix->config);

	pt_encode_tip_pgd(encoder, packet.ip, packet.ipc);

	ptu_check(ptu_sync_decoder, decoder);

	errcode = pt_qry_event(decoder, &event, sizeof(event));
	ptu_int_eq(errcode, pts_eos);
	if (ipc == pt_ipc_suppressed)
		ptu_uint_ne(event.ip_suppressed, 0);
	else {
		ptu_uint_eq(event.ip_suppressed, 0);
		ptu_uint_eq(event.variant.disabled.ip, dfix->last_ip.ip);
	}
	ptu_int_eq(event.type, ptev_disabled);

	if (!tsc)
		ptu_int_eq(event.has_tsc, 0);
	else {
		ptu_int_eq(event.has_tsc, 1);
		ptu_uint_eq(event.tsc, tsc);
	}

	return ptu_passed();
}