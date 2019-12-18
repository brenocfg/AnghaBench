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
struct pt_query_decoder {int dummy; } ;
struct ptu_decoder_fixture {struct pt_query_decoder decoder; } ;

/* Variables and functions */
 int pt_qry_time (struct pt_query_decoder*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pte_invalid ; 
 int /*<<< orphan*/  ptu_int_eq (int,int /*<<< orphan*/ ) ; 
 struct ptunit_result ptu_passed () ; 

__attribute__((used)) static struct ptunit_result time_null_fail(struct ptu_decoder_fixture *dfix)
{
	struct pt_query_decoder *decoder = &dfix->decoder;
	uint64_t tsc;
	int errcode;

	errcode = pt_qry_time(NULL, NULL, NULL, NULL);
	ptu_int_eq(errcode, -pte_invalid);

	errcode = pt_qry_time(decoder, NULL, NULL, NULL);
	ptu_int_eq(errcode, -pte_invalid);

	errcode = pt_qry_time(NULL, &tsc, NULL, NULL);
	ptu_int_eq(errcode, -pte_invalid);

	return ptu_passed();
}