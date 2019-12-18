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

/* Variables and functions */
 int /*<<< orphan*/  cutoff ; 
 int /*<<< orphan*/  pt_encode_cyc (struct pt_encoder*,int) ; 
 int /*<<< orphan*/  pt_encode_tip (struct pt_encoder*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pt_ipc_full ; 
 int pt_qry_indirect_branch (struct pt_query_decoder*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pts_eos ; 
 int /*<<< orphan*/  ptu_check (int /*<<< orphan*/ ,struct pt_query_decoder*,...) ; 
 int /*<<< orphan*/  ptu_int_eq (int,int /*<<< orphan*/ ) ; 
 struct ptunit_result ptu_passed () ; 
 int /*<<< orphan*/  ptu_sync_decoder ; 

__attribute__((used)) static struct ptunit_result indir_cyc_cutoff(struct ptu_decoder_fixture *dfix)
{
	struct pt_query_decoder *decoder = &dfix->decoder;
	struct pt_encoder *encoder = &dfix->encoder;
	uint64_t ip;
	int errcode;

	pt_encode_tip(encoder, 0xa000ull, pt_ipc_full);
	pt_encode_cyc(encoder, 0xfff);

	ptu_check(cutoff, decoder, encoder);
	ptu_check(ptu_sync_decoder, decoder);

	errcode = pt_qry_indirect_branch(decoder, &ip);
	ptu_int_eq(errcode, pts_eos);

	return ptu_passed();
}