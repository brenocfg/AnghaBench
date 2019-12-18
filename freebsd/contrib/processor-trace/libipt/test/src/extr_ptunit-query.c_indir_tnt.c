#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
struct ptunit_result {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  ip; } ;
struct pt_encoder {int dummy; } ;
struct pt_query_decoder {int dummy; } ;
struct ptu_decoder_fixture {TYPE_1__ last_ip; int /*<<< orphan*/  config; struct pt_encoder encoder; struct pt_query_decoder decoder; } ;
struct pt_packet_ip {int ipc; int /*<<< orphan*/  ip; } ;
typedef  enum pt_ip_compression { ____Placeholder_pt_ip_compression } pt_ip_compression ;

/* Variables and functions */
 int /*<<< orphan*/  pt_dfix_bad_ip ; 
 int /*<<< orphan*/  pt_dfix_sext_ip ; 
 int /*<<< orphan*/  pt_encode_tip (struct pt_encoder*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pt_encode_tnt_8 (struct pt_encoder*,unsigned long long,int) ; 
 int pt_ipc_suppressed ; 
 int /*<<< orphan*/  pt_last_ip_update_ip (TYPE_1__*,struct pt_packet_ip*,int /*<<< orphan*/ *) ; 
 int pt_qry_indirect_branch (struct pt_query_decoder*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pts_ip_suppressed ; 
 int /*<<< orphan*/  ptu_check (int /*<<< orphan*/ ,struct pt_query_decoder*) ; 
 int /*<<< orphan*/  ptu_int_eq (int,int /*<<< orphan*/ ) ; 
 struct ptunit_result ptu_passed () ; 
 int /*<<< orphan*/  ptu_sync_decoder ; 
 int /*<<< orphan*/  ptu_uint_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct ptunit_result indir_tnt(struct ptu_decoder_fixture *dfix,
				      enum pt_ip_compression ipc)
{
	struct pt_query_decoder *decoder = &dfix->decoder;
	struct pt_encoder *encoder = &dfix->encoder;
	struct pt_packet_ip packet;
	uint64_t addr = pt_dfix_bad_ip;
	int errcode;

	packet.ipc = ipc;
	packet.ip = pt_dfix_sext_ip;
	pt_last_ip_update_ip(&dfix->last_ip, &packet, &dfix->config);

	pt_encode_tnt_8(encoder, 0ull, 1);
	pt_encode_tip(encoder, packet.ip, packet.ipc);

	ptu_check(ptu_sync_decoder, decoder);

	errcode = pt_qry_indirect_branch(decoder, &addr);
	if (ipc == pt_ipc_suppressed) {
		ptu_int_eq(errcode, pts_ip_suppressed);
		ptu_uint_eq(addr, pt_dfix_bad_ip);
	} else {
		ptu_int_eq(errcode, 0);
		ptu_uint_eq(addr, dfix->last_ip.ip);
	}

	return ptu_passed();
}