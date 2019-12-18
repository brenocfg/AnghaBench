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
struct pt_encoder {int /*<<< orphan*/ * pos; } ;
struct pt_query_decoder {int /*<<< orphan*/  pos; } ;
struct ptu_decoder_fixture {struct pt_encoder encoder; struct pt_query_decoder decoder; } ;

/* Variables and functions */
 int /*<<< orphan*/  pt_encode_tip_pgd (struct pt_encoder*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pt_encode_tnt_8 (struct pt_encoder*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pt_ipc_sext_48 ; 
 int pt_qry_cond_branch (struct pt_query_decoder*,int*) ; 
 int pte_bad_query ; 
 int /*<<< orphan*/  ptu_check (int /*<<< orphan*/ ,struct pt_query_decoder*) ; 
 int /*<<< orphan*/  ptu_int_eq (int,int) ; 
 struct ptunit_result ptu_passed () ; 
 int /*<<< orphan*/  ptu_ptr_eq (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ptu_sync_decoder ; 

__attribute__((used)) static struct ptunit_result
cond_skip_tip_pgd_fail(struct ptu_decoder_fixture *dfix)
{
	struct pt_query_decoder *decoder = &dfix->decoder;
	struct pt_encoder *encoder = &dfix->encoder;
	int errcode, tnt = 0xbc, taken = tnt;
	const uint8_t *pos;

	pos = encoder->pos;
	pt_encode_tip_pgd(encoder, 0, pt_ipc_sext_48);
	pt_encode_tnt_8(encoder, 0, 1);

	ptu_check(ptu_sync_decoder, decoder);

	errcode = pt_qry_cond_branch(decoder, &taken);
	ptu_int_eq(errcode, -pte_bad_query);
	ptu_ptr_eq(decoder->pos, pos);
	ptu_int_eq(taken, tnt);

	return ptu_passed();
}