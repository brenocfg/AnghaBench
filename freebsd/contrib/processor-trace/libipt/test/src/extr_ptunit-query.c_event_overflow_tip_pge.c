#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
struct ptunit_result {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  ip; } ;
struct pt_encoder {int dummy; } ;
struct pt_query_decoder {int dummy; } ;
struct ptu_decoder_fixture {TYPE_3__ last_ip; int /*<<< orphan*/  config; struct pt_encoder encoder; struct pt_query_decoder decoder; } ;
struct pt_packet_ip {int ipc; int ip; } ;
struct TYPE_5__ {int /*<<< orphan*/  ip; } ;
struct TYPE_6__ {TYPE_1__ enabled; } ;
struct pt_event {int type; int has_tsc; int /*<<< orphan*/  tsc; TYPE_2__ variant; int /*<<< orphan*/  ip_suppressed; } ;
typedef  int /*<<< orphan*/  event ;
typedef  enum pt_ip_compression { ____Placeholder_pt_ip_compression } pt_ip_compression ;

/* Variables and functions */
 int /*<<< orphan*/  pt_encode_ovf (struct pt_encoder*) ; 
 int /*<<< orphan*/  pt_encode_tip_pge (struct pt_encoder*,int,int) ; 
#define  pt_ipc_full 133 
#define  pt_ipc_sext_48 132 
#define  pt_ipc_suppressed 131 
#define  pt_ipc_update_16 130 
#define  pt_ipc_update_32 129 
#define  pt_ipc_update_48 128 
 int /*<<< orphan*/  pt_last_ip_init (TYPE_3__*) ; 
 int /*<<< orphan*/  pt_last_ip_update_ip (TYPE_3__*,struct pt_packet_ip*,int /*<<< orphan*/ *) ; 
 int pt_qry_event (struct pt_query_decoder*,struct pt_event*,int) ; 
 int pte_bad_packet ; 
 int ptev_enabled ; 
 int ptev_overflow ; 
 int pts_eos ; 
 int pts_event_pending ; 
 int /*<<< orphan*/  ptu_check (int /*<<< orphan*/ ,struct pt_query_decoder*) ; 
 int /*<<< orphan*/  ptu_int_eq (int,int) ; 
 struct ptunit_result ptu_passed () ; 
 int /*<<< orphan*/  ptu_sync_decoder ; 
 int /*<<< orphan*/  ptu_uint_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ptu_uint_ne (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct ptunit_result
event_overflow_tip_pge(struct ptu_decoder_fixture *dfix,
		       enum pt_ip_compression ipc, uint64_t tsc)
{
	struct pt_query_decoder *decoder = &dfix->decoder;
	struct pt_encoder *encoder = &dfix->encoder;
	struct pt_event event;
	struct pt_packet_ip packet;
	int errcode;

	packet.ipc = ipc;
	packet.ip = 0xccull;

	pt_last_ip_init(&dfix->last_ip);
	pt_last_ip_update_ip(&dfix->last_ip, &packet, &dfix->config);

	pt_encode_ovf(encoder);
	pt_encode_tip_pge(encoder, packet.ip, packet.ipc);

	ptu_check(ptu_sync_decoder, decoder);

	errcode = pt_qry_event(decoder, &event, sizeof(event));
	ptu_int_eq(errcode, pts_event_pending);
	ptu_int_eq(event.type, ptev_overflow);
	ptu_uint_ne(event.ip_suppressed, 0);

	if (!tsc)
		ptu_int_eq(event.has_tsc, 0);
	else {
		ptu_int_eq(event.has_tsc, 1);
		ptu_uint_eq(event.tsc, tsc);
	}

	errcode = pt_qry_event(decoder, &event, sizeof(event));
	switch (ipc) {
	case pt_ipc_suppressed:
		ptu_int_eq(errcode, -pte_bad_packet);
		break;

	case pt_ipc_update_16:
	case pt_ipc_update_32:
	case pt_ipc_update_48:
	case pt_ipc_sext_48:
	case pt_ipc_full:
		ptu_int_eq(errcode, pts_eos);
		ptu_int_eq(event.type, ptev_enabled);
		ptu_uint_eq(event.variant.enabled.ip, dfix->last_ip.ip);

		if (!tsc)
			ptu_int_eq(event.has_tsc, 0);
		else {
			ptu_int_eq(event.has_tsc, 1);
			ptu_uint_eq(event.tsc, tsc);
		}
		break;
	}

	return ptu_passed();
}