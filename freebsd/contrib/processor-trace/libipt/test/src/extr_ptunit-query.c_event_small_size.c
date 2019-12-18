#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct ptunit_result {int dummy; } ;
struct pt_encoder {int dummy; } ;
struct pt_query_decoder {int dummy; } ;
struct ptu_decoder_fixture {struct pt_encoder encoder; struct pt_query_decoder decoder; } ;
struct pt_event {int type; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  pt_encode_tip_pge (struct pt_encoder*,unsigned long long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pt_ipc_sext_48 ; 
 int pt_qry_event (struct pt_query_decoder*,struct pt_event*,int) ; 
 int /*<<< orphan*/  ptev_enabled ; 
 int /*<<< orphan*/  pts_eos ; 
 int /*<<< orphan*/  ptu_check (int /*<<< orphan*/ ,struct pt_query_decoder*) ; 
 int /*<<< orphan*/  ptu_int_eq (int,int /*<<< orphan*/ ) ; 
 struct ptunit_result ptu_passed () ; 
 int /*<<< orphan*/  ptu_sync_decoder ; 
 int /*<<< orphan*/  ptu_uint_eq (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static struct ptunit_result event_small_size(struct ptu_decoder_fixture *dfix)
{
	struct pt_query_decoder *decoder = &dfix->decoder;
	struct pt_encoder *encoder = &dfix->encoder;
	union {
		struct pt_event event;
		uint8_t buffer[41];
	} variant;
	int errcode;

	memset(variant.buffer, 0xcd, sizeof(variant.buffer));

	pt_encode_tip_pge(encoder, 0ull, pt_ipc_sext_48);

	ptu_check(ptu_sync_decoder, decoder);

	errcode = pt_qry_event(decoder, &variant.event, 40);
	ptu_int_eq(errcode, pts_eos);
	ptu_int_eq(variant.event.type, ptev_enabled);
	ptu_uint_eq(variant.buffer[40], 0xcd);

	return ptu_passed();
}