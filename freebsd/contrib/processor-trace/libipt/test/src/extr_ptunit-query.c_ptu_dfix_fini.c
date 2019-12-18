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
struct ptu_decoder_fixture {int /*<<< orphan*/  encoder; int /*<<< orphan*/  decoder; } ;

/* Variables and functions */
 int /*<<< orphan*/  pt_encoder_fini (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pt_qry_decoder_fini (int /*<<< orphan*/ *) ; 
 struct ptunit_result ptu_passed () ; 

__attribute__((used)) static struct ptunit_result ptu_dfix_fini(struct ptu_decoder_fixture *dfix)
{
	pt_qry_decoder_fini(&dfix->decoder);
	pt_encoder_fini(&dfix->encoder);

	return ptu_passed();
}