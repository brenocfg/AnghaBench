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
typedef  unsigned long long uint64_t ;
struct ptunit_result {int dummy; } ;
struct TYPE_6__ {unsigned long long ip; } ;
struct pt_encoder {int dummy; } ;
struct pt_query_decoder {int dummy; } ;
struct ptu_decoder_fixture {TYPE_3__ last_ip; int /*<<< orphan*/  config; struct pt_encoder encoder; struct pt_query_decoder decoder; } ;
struct pt_packet_ip {int ipc; int /*<<< orphan*/  ip; } ;
struct TYPE_4__ {unsigned long long ip; int mode; } ;
struct TYPE_5__ {TYPE_1__ exec_mode; } ;
struct pt_event {unsigned long long ip_suppressed; int type; int has_tsc; unsigned long long tsc; TYPE_2__ variant; } ;
typedef  int /*<<< orphan*/  event ;
typedef  enum pt_ip_compression { ____Placeholder_pt_ip_compression } pt_ip_compression ;
typedef  enum pt_exec_mode { ____Placeholder_pt_exec_mode } pt_exec_mode ;

/* Variables and functions */
 int /*<<< orphan*/  pt_dfix_max_ip ; 
 int /*<<< orphan*/  pt_encode_mode_exec (struct pt_encoder*,int) ; 
 int /*<<< orphan*/  pt_encode_tip (struct pt_encoder*,int /*<<< orphan*/ ,int) ; 
 int pt_ipc_suppressed ; 
 int /*<<< orphan*/  pt_last_ip_update_ip (TYPE_3__*,struct pt_packet_ip*,int /*<<< orphan*/ *) ; 
 int pt_qry_event (struct pt_query_decoder*,struct pt_event*,int) ; 
 int pt_qry_indirect_branch (struct pt_query_decoder*,unsigned long long*) ; 
 int ptem_16bit ; 
 int ptev_exec_mode ; 
 int pts_eos ; 
 int pts_ip_suppressed ; 
 int /*<<< orphan*/  ptu_check (int /*<<< orphan*/ ,struct pt_query_decoder*) ; 
 int /*<<< orphan*/  ptu_int_eq (int,int) ; 
 struct ptunit_result ptu_passed () ; 
 int /*<<< orphan*/  ptu_sync_decoder ; 
 int /*<<< orphan*/  ptu_uint_eq (unsigned long long,unsigned long long) ; 
 int /*<<< orphan*/  ptu_uint_ne (unsigned long long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct ptunit_result
event_exec_mode_tip(struct ptu_decoder_fixture *dfix,
		    enum pt_ip_compression ipc, uint64_t tsc)
{
	struct pt_query_decoder *decoder = &dfix->decoder;
	struct pt_encoder *encoder = &dfix->encoder;
	enum pt_exec_mode mode = ptem_16bit;
	struct pt_packet_ip packet;
	struct pt_event event;
	uint64_t addr = 0ull;
	int errcode;

	packet.ipc = ipc;
	packet.ip = pt_dfix_max_ip;
	pt_last_ip_update_ip(&dfix->last_ip, &packet, &dfix->config);

	pt_encode_mode_exec(encoder, mode);
	pt_encode_tip(encoder, packet.ip, packet.ipc);

	ptu_check(ptu_sync_decoder, decoder);

	errcode = pt_qry_event(decoder, &event, sizeof(event));
	ptu_int_eq(errcode, 0);
	if (ipc == pt_ipc_suppressed)
		ptu_uint_ne(event.ip_suppressed, 0);
	else {
		ptu_uint_eq(event.ip_suppressed, 0);
		ptu_uint_eq(event.variant.exec_mode.ip, dfix->last_ip.ip);
	}
	ptu_int_eq(event.type, ptev_exec_mode);
	ptu_int_eq(event.variant.exec_mode.mode, mode);

	if (!tsc)
		ptu_int_eq(event.has_tsc, 0);
	else {
		ptu_int_eq(event.has_tsc, 1);
		ptu_uint_eq(event.tsc, tsc);
	}

	errcode = pt_qry_indirect_branch(decoder, &addr);
	if (ipc == pt_ipc_suppressed)
		ptu_int_eq(errcode, pts_ip_suppressed | pts_eos);
	else {
		ptu_int_eq(errcode, pts_eos);
		ptu_uint_eq(addr, dfix->last_ip.ip);
	}

	return ptu_passed();
}