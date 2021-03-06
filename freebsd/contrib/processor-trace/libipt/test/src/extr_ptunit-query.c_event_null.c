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
struct pt_event {int dummy; } ;
typedef  int /*<<< orphan*/  event ;

/* Variables and functions */
 int pt_qry_event (struct pt_query_decoder*,struct pt_event*,int) ; 
 int /*<<< orphan*/  pte_invalid ; 
 int /*<<< orphan*/  ptu_int_eq (int,int /*<<< orphan*/ ) ; 
 struct ptunit_result ptu_passed () ; 
 int /*<<< orphan*/  ptu_ptr_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct ptunit_result event_null(struct ptu_decoder_fixture *dfix)
{
	struct pt_query_decoder *decoder = &dfix->decoder;
	struct pt_config *config = &decoder->config;
	struct pt_event event;
	int errcode;

	errcode = pt_qry_event(NULL, &event, sizeof(event));
	ptu_int_eq(errcode, -pte_invalid);

	errcode = pt_qry_event(decoder, NULL, sizeof(event));
	ptu_int_eq(errcode, -pte_invalid);
	ptu_ptr_eq(decoder->pos, config->begin);

	return ptu_passed();
}