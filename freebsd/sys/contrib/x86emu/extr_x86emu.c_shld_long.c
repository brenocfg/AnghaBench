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
typedef  unsigned int uint32_t ;
struct x86emu {int dummy; } ;

/* Variables and functions */
 scalar_t__ ACCESS_FLAG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CLEAR_FLAG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CONDITIONAL_SET_FLAG (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  F_CF ; 
 int /*<<< orphan*/  F_OF ; 
 int /*<<< orphan*/  F_PF ; 
 int /*<<< orphan*/  F_SF ; 
 int /*<<< orphan*/  F_ZF ; 
 unsigned int PARITY (unsigned int) ; 
 int /*<<< orphan*/  SET_FLAG (int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint32_t 
shld_long(struct x86emu *emu, uint32_t d, uint32_t fill, uint8_t s)
{
	unsigned int cnt, res, cf;

	if (s < 32) {
		cnt = s % 32;
		if (cnt > 0) {
			res = (d << cnt) | (fill >> (32 - cnt));
			cf = d & (1 << (32 - cnt));
			CONDITIONAL_SET_FLAG(cf, F_CF);
			CONDITIONAL_SET_FLAG((res & 0xffffffff) == 0, F_ZF);
			CONDITIONAL_SET_FLAG(res & 0x80000000, F_SF);
			CONDITIONAL_SET_FLAG(PARITY(res & 0xff), F_PF);
		} else {
			res = d;
		}
		if (cnt == 1) {
			CONDITIONAL_SET_FLAG((((res & 0x80000000) == 0x80000000)
			    ^ (ACCESS_FLAG(F_CF) != 0)), F_OF);
		} else {
			CLEAR_FLAG(F_OF);
		}
	} else {
		res = 0;
		CONDITIONAL_SET_FLAG((d << (s - 1)) & 0x80000000, F_CF);
		CLEAR_FLAG(F_OF);
		CLEAR_FLAG(F_SF);
		SET_FLAG(F_PF);
		SET_FLAG(F_ZF);
	}
	return res;
}