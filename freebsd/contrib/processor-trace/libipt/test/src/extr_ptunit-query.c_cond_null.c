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
struct ptunit_result {int dummy; } ;
struct pt_config {int /*<<< orphan*/  begin; } ;
struct pt_query_decoder {int /*<<< orphan*/  pos; struct pt_config config; } ;
struct ptu_decoder_fixture {struct pt_query_decoder decoder; } ;

/* Variables and functions */
 int pt_qry_cond_branch (struct pt_query_decoder*,int*) ; 
 int pte_invalid ; 
 int /*<<< orphan*/  ptu_int_eq (int,int) ; 
 struct ptunit_result ptu_passed () ; 
 int /*<<< orphan*/  ptu_ptr_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct ptunit_result cond_null(struct ptu_decoder_fixture *dfix)
{
	struct pt_query_decoder *decoder = &dfix->decoder;
	struct pt_config *config = &decoder->config;
	int errcode, tnt = 0xbc, taken = tnt;

	errcode = pt_qry_cond_branch(NULL, &taken);
	ptu_int_eq(errcode, -pte_invalid);
	ptu_int_eq(taken, tnt);

	errcode = pt_qry_cond_branch(decoder, NULL);
	ptu_int_eq(errcode, -pte_invalid);
	ptu_ptr_eq(decoder->pos, config->begin);

	return ptu_passed();
}