#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int uint64_t ;
struct ptunit_result {int dummy; } ;
struct pt_encoder {int dummy; } ;
struct pt_query_decoder {int dummy; } ;
struct ptu_decoder_fixture {struct pt_encoder encoder; struct pt_query_decoder decoder; } ;
struct TYPE_3__ {int /*<<< orphan*/  non_root; int /*<<< orphan*/  cr3; } ;
struct TYPE_4__ {TYPE_1__ paging; } ;
struct pt_event {int type; int has_tsc; int /*<<< orphan*/  tsc; TYPE_2__ variant; } ;
typedef  int /*<<< orphan*/  event ;

/* Variables and functions */
 int pt_dfix_max_cr3 ; 
 int /*<<< orphan*/  pt_encode_pip (struct pt_encoder*,int,int) ; 
 int pt_pl_pip_nr ; 
 int pt_qry_event (struct pt_query_decoder*,struct pt_event*,int) ; 
 int ptev_paging ; 
 int pts_eos ; 
 int /*<<< orphan*/  ptu_check (int /*<<< orphan*/ ,struct pt_query_decoder*) ; 
 int /*<<< orphan*/  ptu_int_eq (int,int) ; 
 struct ptunit_result ptu_passed () ; 
 int /*<<< orphan*/  ptu_sync_decoder ; 
 int /*<<< orphan*/  ptu_uint_eq (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static struct ptunit_result event_paging(struct ptu_decoder_fixture *dfix,
					 uint8_t flags, uint64_t tsc)
{
	struct pt_query_decoder *decoder = &dfix->decoder;
	struct pt_encoder *encoder = &dfix->encoder;
	struct pt_event event;
	uint64_t cr3 = pt_dfix_max_cr3;
	int errcode;

	pt_encode_pip(encoder, cr3, flags);

	ptu_check(ptu_sync_decoder, decoder);

	errcode = pt_qry_event(decoder, &event, sizeof(event));
	ptu_int_eq(errcode, pts_eos);
	ptu_int_eq(event.type, ptev_paging);
	ptu_uint_eq(event.variant.paging.cr3, cr3);
	ptu_uint_eq(event.variant.paging.non_root, (flags & pt_pl_pip_nr) != 0);

	if (!tsc)
		ptu_int_eq(event.has_tsc, 0);
	else {
		ptu_int_eq(event.has_tsc, 1);
		ptu_uint_eq(event.tsc, tsc);
	}

	return ptu_passed();
}