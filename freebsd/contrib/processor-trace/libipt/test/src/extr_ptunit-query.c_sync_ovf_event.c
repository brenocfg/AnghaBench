#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
struct ptunit_result {int dummy; } ;
struct TYPE_9__ {int ip; } ;
struct pt_encoder {int dummy; } ;
struct pt_query_decoder {int dummy; } ;
struct ptu_decoder_fixture {TYPE_4__ last_ip; int /*<<< orphan*/  config; struct pt_encoder encoder; struct pt_query_decoder decoder; } ;
struct pt_packet_ip {int ipc; int ip; } ;
struct TYPE_7__ {int /*<<< orphan*/  ip; } ;
struct TYPE_6__ {int speculative; int aborted; int /*<<< orphan*/  ip; } ;
struct TYPE_8__ {TYPE_2__ overflow; TYPE_1__ tsx; } ;
struct pt_event {int type; int has_tsc; int /*<<< orphan*/  tsc; TYPE_3__ variant; int /*<<< orphan*/  status_update; } ;
typedef  int /*<<< orphan*/  event ;
typedef  enum pt_ip_compression { ____Placeholder_pt_ip_compression } pt_ip_compression ;

/* Variables and functions */
 int pt_dfix_max_ip ; 
 int /*<<< orphan*/  pt_encode_fup (struct pt_encoder*,int,int) ; 
 int /*<<< orphan*/  pt_encode_mode_tsx (struct pt_encoder*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pt_encode_ovf (struct pt_encoder*) ; 
 int /*<<< orphan*/  pt_encode_psb (struct pt_encoder*) ; 
 int /*<<< orphan*/  pt_encode_tsc (struct pt_encoder*,int) ; 
#define  pt_ipc_full 133 
#define  pt_ipc_sext_48 132 
#define  pt_ipc_suppressed 131 
#define  pt_ipc_update_16 130 
#define  pt_ipc_update_32 129 
#define  pt_ipc_update_48 128 
 int /*<<< orphan*/  pt_last_ip_init (TYPE_4__*) ; 
 int /*<<< orphan*/  pt_last_ip_update_ip (TYPE_4__*,struct pt_packet_ip*,int /*<<< orphan*/ *) ; 
 int pt_qry_event (struct pt_query_decoder*,struct pt_event*,int) ; 
 int pt_qry_sync_forward (struct pt_query_decoder*,int /*<<< orphan*/ *) ; 
 int pte_noip ; 
 int ptev_overflow ; 
 int ptev_tsx ; 
 int pts_eos ; 
 int pts_event_pending ; 
 int /*<<< orphan*/  ptu_int_eq (int,int) ; 
 struct ptunit_result ptu_passed () ; 
 int /*<<< orphan*/  ptu_uint_eq (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ptu_uint_ne (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct ptunit_result sync_ovf_event(struct ptu_decoder_fixture *dfix,
					   enum pt_ip_compression ipc)
{
	struct pt_query_decoder *decoder = &dfix->decoder;
	struct pt_encoder *encoder = &dfix->encoder;
	struct pt_packet_ip fup, ovf;
	struct pt_event event;
	uint64_t addr = 0;
	int errcode;

	fup.ipc = pt_ipc_sext_48;
	fup.ip = pt_dfix_max_ip;

	ovf.ipc = ipc;
	ovf.ip = 0xccull;

	pt_last_ip_init(&dfix->last_ip);
	pt_last_ip_update_ip(&dfix->last_ip, &ovf, &dfix->config);

	pt_encode_psb(encoder);
	pt_encode_fup(encoder, fup.ip, fup.ipc);
	pt_encode_mode_tsx(encoder, 0);
	pt_encode_tsc(encoder, 0x1000);
	pt_encode_ovf(encoder);
	pt_encode_fup(encoder, ovf.ip, ovf.ipc);

	errcode = pt_qry_sync_forward(decoder, &addr);
	ptu_int_eq(errcode, pts_event_pending);
	ptu_uint_eq(addr, fup.ip);

	errcode = pt_qry_event(decoder, &event, sizeof(event));
	ptu_int_eq(errcode, pts_event_pending);
	ptu_uint_ne(event.status_update, 0);
	ptu_int_eq(event.type, ptev_tsx);
	ptu_int_eq(event.variant.tsx.speculative, 0);
	ptu_int_eq(event.variant.tsx.aborted, 0);
	ptu_uint_eq(event.variant.tsx.ip, fup.ip);
	ptu_int_eq(event.has_tsc, 1);
	ptu_uint_eq(event.tsc, 0x1000);

	errcode = pt_qry_event(decoder, &event, sizeof(event));
	switch (ipc) {
	case pt_ipc_suppressed:
		ptu_int_eq(errcode, -pte_noip);
		return ptu_passed();

	case pt_ipc_update_16:
	case pt_ipc_update_32:
	case pt_ipc_update_48:
	case pt_ipc_sext_48:
	case pt_ipc_full:
		ptu_int_eq(errcode, pts_eos);
		ptu_int_eq(event.type, ptev_overflow);
		ptu_uint_eq(event.variant.overflow.ip, dfix->last_ip.ip);
		ptu_int_eq(event.has_tsc, 1);
		ptu_uint_eq(event.tsc, 0x1000);
		break;
	}

	return ptu_passed();
}