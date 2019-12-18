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
struct pt_block {int dummy; } ;
typedef  int /*<<< orphan*/  block ;

/* Variables and functions */
 int pt_blk_next (struct pt_block_decoder*,struct pt_block*,int) ; 
 int /*<<< orphan*/  pte_invalid ; 
 int /*<<< orphan*/  ptu_int_eq (int,int /*<<< orphan*/ ) ; 
 struct ptunit_result ptu_passed () ; 

__attribute__((used)) static struct ptunit_result next_null(void)
{
	struct pt_block_decoder decoder;
	struct pt_block block;
	int errcode;

	errcode = pt_blk_next(NULL, &block, sizeof(block));
	ptu_int_eq(errcode, -pte_invalid);

	errcode = pt_blk_next(&decoder, NULL, sizeof(block));
	ptu_int_eq(errcode, -pte_invalid);

	return ptu_passed();
}