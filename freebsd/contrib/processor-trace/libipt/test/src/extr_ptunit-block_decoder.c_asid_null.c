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
struct pt_block_decoder {int dummy; } ;
struct pt_asid {int dummy; } ;
typedef  int /*<<< orphan*/  asid ;

/* Variables and functions */
 int pt_blk_asid (struct pt_block_decoder*,struct pt_asid*,int) ; 
 int /*<<< orphan*/  pte_invalid ; 
 int /*<<< orphan*/  ptu_int_eq (int,int /*<<< orphan*/ ) ; 
 struct ptunit_result ptu_passed () ; 

__attribute__((used)) static struct ptunit_result asid_null(void)
{
	struct pt_block_decoder decoder;
	struct pt_asid asid;
	int errcode;

	errcode = pt_blk_asid(NULL, &asid, sizeof(asid));
	ptu_int_eq(errcode, -pte_invalid);

	errcode = pt_blk_asid(&decoder, NULL, sizeof(asid));
	ptu_int_eq(errcode, -pte_invalid);

	return ptu_passed();
}