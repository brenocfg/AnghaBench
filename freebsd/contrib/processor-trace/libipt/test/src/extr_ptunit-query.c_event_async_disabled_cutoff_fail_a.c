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
typedef  int /*<<< orphan*/  uint64_t ;
struct ptunit_result {int dummy; } ;
struct pt_encoder {int dummy; } ;
struct pt_query_decoder {int dummy; } ;
struct ptu_decoder_fixture {struct pt_encoder encoder; struct pt_query_decoder decoder; } ;
struct pt_event {int dummy; } ;
typedef  int /*<<< orphan*/  event ;

/* Variables and functions */
 int /*<<< orphan*/  cutoff ; 
 int /*<<< orphan*/  pt_dfix_sext_ip ; 
 int /*<<< orphan*/  pt_encode_fup (struct pt_encoder*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pt_encode_tip_pgd (struct pt_encoder*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pt_ipc_sext_48 ; 
 int /*<<< orphan*/  pt_ipc_update_16 ; 
 int pt_qry_event (struct pt_query_decoder*,struct pt_event*,int) ; 
 int /*<<< orphan*/  pte_eos ; 
 int /*<<< orphan*/  ptu_check (int /*<<< orphan*/ ,struct pt_query_decoder*,...) ; 
 int /*<<< orphan*/  ptu_int_eq (int,int /*<<< orphan*/ ) ; 
 struct ptunit_result ptu_passed () ; 
 int /*<<< orphan*/  ptu_sync_decoder ; 

__attribute__((used)) static struct ptunit_result
event_async_disabled_cutoff_fail_a(struct ptu_decoder_fixture *dfix)
{
	struct pt_query_decoder *decoder = &dfix->decoder;
	struct pt_encoder *encoder = &dfix->encoder;
	struct pt_event event;
	uint64_t at = pt_dfix_sext_ip;
	int errcode;

	pt_encode_fup(encoder, at, pt_ipc_sext_48);
	pt_encode_tip_pgd(encoder, 0, pt_ipc_update_16);

	ptu_check(cutoff, decoder, encoder);
	ptu_check(ptu_sync_decoder, decoder);

	errcode = pt_qry_event(decoder, &event, sizeof(event));
	ptu_int_eq(errcode, -pte_eos);

	return ptu_passed();
}