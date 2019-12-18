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
struct ptunit_result {int dummy; } ;
struct pt_decoder_function {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  end; } ;
struct fetch_fixture {TYPE_1__ config; } ;

/* Variables and functions */
 int pt_df_fetch (struct pt_decoder_function const**,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  pte_eos ; 
 int /*<<< orphan*/  ptu_int_eq (int,int /*<<< orphan*/ ) ; 
 struct ptunit_result ptu_passed () ; 

__attribute__((used)) static struct ptunit_result fetch_empty(struct fetch_fixture *ffix)
{
	const struct pt_decoder_function *dfun;
	int errcode;

	errcode = pt_df_fetch(&dfun, ffix->config.end, &ffix->config);
	ptu_int_eq(errcode, -pte_eos);

	return ptu_passed();
}