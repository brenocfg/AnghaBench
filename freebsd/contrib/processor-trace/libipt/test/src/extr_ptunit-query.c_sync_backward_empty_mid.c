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
 int pt_enc_get_offset (struct pt_encoder*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pt_encode_mode_exec (struct pt_encoder*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pt_encode_psb (struct pt_encoder*) ; 
 int /*<<< orphan*/  pt_encode_psbend (struct pt_encoder*) ; 
 int pt_qry_get_sync_offset (struct pt_query_decoder*,int /*<<< orphan*/ *) ; 
 int pt_qry_sync_backward (struct pt_query_decoder*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pte_eos ; 
 int /*<<< orphan*/  ptem_64bit ; 
 int /*<<< orphan*/  ptu_int_eq (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ptu_int_ge (int,int /*<<< orphan*/ ) ; 
 struct ptunit_result ptu_passed () ; 
 int /*<<< orphan*/  ptu_uint_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct ptunit_result
sync_backward_empty_mid(struct ptu_decoder_fixture *dfix)
{
	struct pt_query_decoder *decoder = &dfix->decoder;
	struct pt_encoder *encoder = &dfix->encoder;
	uint64_t sync[3], offset, ip;
	int errcode;

	/* Check that we can use repeated pt_qry_sync_backward() to iterate over
	 * synchronization points in backwards order.
	 *
	 * There's an empty PSB+ in the middle.  We skip it.
	 */

	errcode = pt_enc_get_offset(encoder, &sync[0]);
	ptu_int_ge(errcode, 0);

	pt_encode_psb(encoder);
	pt_encode_mode_exec(encoder, ptem_64bit);
	pt_encode_psbend(encoder);

	errcode = pt_enc_get_offset(encoder, &sync[1]);
	ptu_int_ge(errcode, 0);

	pt_encode_psb(encoder);
	pt_encode_psbend(encoder);

	errcode = pt_enc_get_offset(encoder, &sync[2]);
	ptu_int_ge(errcode, 0);

	pt_encode_psb(encoder);
	pt_encode_mode_exec(encoder, ptem_64bit);
	pt_encode_psbend(encoder);

	/* Synchronize repeatedly and check that we reach each PSB in the
	 * correct order.
	 */

	errcode = pt_qry_sync_backward(decoder, &ip);
	ptu_int_ge(errcode, 0);

	errcode = pt_qry_get_sync_offset(decoder, &offset);
	ptu_int_eq(errcode, 0);
	ptu_uint_eq(offset, sync[2]);

	errcode = pt_qry_sync_backward(decoder, &ip);
	ptu_int_ge(errcode, 0);

	errcode = pt_qry_get_sync_offset(decoder, &offset);
	ptu_int_eq(errcode, 0);
	ptu_uint_eq(offset, sync[0]);

	errcode = pt_qry_sync_backward(decoder, &ip);
	ptu_int_eq(errcode, -pte_eos);

	return ptu_passed();
}