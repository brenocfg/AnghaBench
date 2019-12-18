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
typedef  int /*<<< orphan*/  uint32_t ;
struct ptunit_result {int dummy; } ;
struct TYPE_2__ {int have_cbr; int cbr; } ;
struct pt_query_decoder {TYPE_1__ last_time; } ;
struct ptu_decoder_fixture {struct pt_query_decoder decoder; } ;

/* Variables and functions */
 int pt_qry_core_bus_ratio (struct pt_query_decoder*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ptu_int_eq (int,int /*<<< orphan*/ ) ; 
 struct ptunit_result ptu_passed () ; 
 int /*<<< orphan*/  ptu_uint_eq (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static struct ptunit_result cbr(struct ptu_decoder_fixture *dfix)
{
	struct pt_query_decoder *decoder = &dfix->decoder;
	uint32_t cbr;
	int errcode;

	decoder->last_time.have_cbr = 1;
	decoder->last_time.cbr = 42;

	errcode = pt_qry_core_bus_ratio(decoder, &cbr);
	ptu_int_eq(errcode, 0);
	ptu_uint_eq(cbr, 42);

	return ptu_passed();
}