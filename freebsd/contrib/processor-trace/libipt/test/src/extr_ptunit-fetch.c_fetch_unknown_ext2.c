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
struct TYPE_2__ {int /*<<< orphan*/ * begin; } ;
struct fetch_fixture {TYPE_1__ config; } ;

/* Variables and functions */
 int /*<<< orphan*/  pt_decode_unknown ; 
 int pt_df_fetch (struct pt_decoder_function const**,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  pt_ext2_bad ; 
 int /*<<< orphan*/  pt_ext_ext2 ; 
 int /*<<< orphan*/  pt_opc_ext ; 
 int /*<<< orphan*/  ptu_int_eq (int,int /*<<< orphan*/ ) ; 
 struct ptunit_result ptu_passed () ; 
 int /*<<< orphan*/  ptu_ptr_eq (struct pt_decoder_function const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct ptunit_result fetch_unknown_ext2(struct fetch_fixture *ffix)
{
	const struct pt_decoder_function *dfun;
	int errcode;

	ffix->config.begin[0] = pt_opc_ext;
	ffix->config.begin[1] = pt_ext_ext2;
	ffix->config.begin[2] = pt_ext2_bad;

	errcode = pt_df_fetch(&dfun, ffix->config.begin, &ffix->config);
	ptu_int_eq(errcode, 0);
	ptu_ptr_eq(dfun, &pt_decode_unknown);

	return ptu_passed();
}