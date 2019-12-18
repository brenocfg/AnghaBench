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
typedef  int /*<<< orphan*/  uint32_t ;
struct ptunit_result {int dummy; } ;
struct pt_block_decoder {int dummy; } ;

/* Variables and functions */
 int pt_blk_core_bus_ratio (struct pt_block_decoder*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pte_invalid ; 
 int /*<<< orphan*/  ptu_int_eq (int,int /*<<< orphan*/ ) ; 
 struct ptunit_result ptu_passed () ; 

__attribute__((used)) static struct ptunit_result cbr_null(void)
{
	struct pt_block_decoder decoder;
	uint32_t cbr;
	int errcode;

	errcode = pt_blk_core_bus_ratio(NULL, &cbr);
	ptu_int_eq(errcode, -pte_invalid);

	errcode = pt_blk_core_bus_ratio(&decoder, NULL);
	ptu_int_eq(errcode, -pte_invalid);

	return ptu_passed();
}