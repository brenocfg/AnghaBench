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
typedef  int uint8_t ;
struct ptunit_result {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ptem_64bit ; 
 int /*<<< orphan*/  ptu_decode_s (int*,int /*<<< orphan*/ ) ; 
 struct ptunit_result ptu_passed () ; 

__attribute__((used)) static struct ptunit_result vmovdqa(void)
{
	uint8_t insn[] = { 0xc5, 0xf9, 0x6f, 0x25, 0xa9, 0x55, 0x04, 0x00 };

	ptu_decode_s(insn, ptem_64bit);

	return ptu_passed();
}