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
struct x86emu {int dummy; } ;

/* Variables and functions */
 scalar_t__ ACCESS_FLAG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CLEAR_FLAG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CONDITIONAL_SET_FLAG (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  F_CF ; 
 int /*<<< orphan*/  F_OF ; 
 int /*<<< orphan*/  F_PF ; 
 int /*<<< orphan*/  F_SF ; 
 int /*<<< orphan*/  F_ZF ; 
 int PARITY (unsigned int) ; 
 int /*<<< orphan*/  SET_FLAG (int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint8_t 
shl_byte(struct x86emu *emu, uint8_t d, uint8_t s)
{
	unsigned int cnt, res, cf;

	if (s < 8) {
		cnt = s % 8;

		/* last bit shifted out goes into carry flag */
		if (cnt > 0) {
			res = d << cnt;
			cf = d & (1 << (8 - cnt));
			CONDITIONAL_SET_FLAG(cf, F_CF);
			CONDITIONAL_SET_FLAG((res & 0xff) == 0, F_ZF);
			CONDITIONAL_SET_FLAG(res & 0x80, F_SF);
			CONDITIONAL_SET_FLAG(PARITY(res & 0xff), F_PF);
		} else {
			res = (uint8_t) d;
		}

		if (cnt == 1) {
			/* Needs simplification. */
			CONDITIONAL_SET_FLAG(
			    (((res & 0x80) == 0x80) ^
				(ACCESS_FLAG(F_CF) != 0)),
			/* was (emu->x86.R_FLG&F_CF)==F_CF)), */
			    F_OF);
		} else {
			CLEAR_FLAG(F_OF);
		}
	} else {
		res = 0;
		CONDITIONAL_SET_FLAG((d << (s - 1)) & 0x80, F_CF);
		CLEAR_FLAG(F_OF);
		CLEAR_FLAG(F_SF);
		SET_FLAG(F_PF);
		SET_FLAG(F_ZF);
	}
	return (uint8_t) res;
}