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
 int /*<<< orphan*/  CLEAR_FLAG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CONDITIONAL_SET_FLAG (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  F_CF ; 
 int /*<<< orphan*/  F_PF ; 
 int /*<<< orphan*/  F_SF ; 
 int /*<<< orphan*/  F_ZF ; 
 unsigned int PARITY (unsigned int) ; 
 int /*<<< orphan*/  SET_FLAG (int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint8_t 
sar_byte(struct x86emu *emu, uint8_t d, uint8_t s)
{
	unsigned int cnt, res, cf, mask, sf;

	res = d;
	sf = d & 0x80;
	cnt = s % 8;
	if (cnt > 0 && cnt < 8) {
		mask = (1 << (8 - cnt)) - 1;
		cf = d & (1 << (cnt - 1));
		res = (d >> cnt) & mask;
		CONDITIONAL_SET_FLAG(cf, F_CF);
		if (sf) {
			res |= ~mask;
		}
		CONDITIONAL_SET_FLAG((res & 0xff) == 0, F_ZF);
		CONDITIONAL_SET_FLAG(PARITY(res & 0xff), F_PF);
		CONDITIONAL_SET_FLAG(res & 0x80, F_SF);
	} else if (cnt >= 8) {
		if (sf) {
			res = 0xff;
			SET_FLAG(F_CF);
			CLEAR_FLAG(F_ZF);
			SET_FLAG(F_SF);
			SET_FLAG(F_PF);
		} else {
			res = 0;
			CLEAR_FLAG(F_CF);
			SET_FLAG(F_ZF);
			CLEAR_FLAG(F_SF);
			CLEAR_FLAG(F_PF);
		}
	}
	return (uint8_t) res;
}