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
 int /*<<< orphan*/  ptem_32bit ; 
 int /*<<< orphan*/  ptu_decode (int*,int,int /*<<< orphan*/ ) ; 
 struct ptunit_result ptu_passed () ; 

__attribute__((used)) static struct ptunit_result mov_al_16_em32(void)
{
	uint8_t insn[] = { 0x67, 0xa0, 0x3f, 0xaa, 0xbb, 0xcc, 0xdd, 0xee };

	ptu_decode(insn, 4, ptem_32bit);

	return ptu_passed();
}