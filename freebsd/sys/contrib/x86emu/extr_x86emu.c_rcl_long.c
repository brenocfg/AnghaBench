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
typedef  int uint32_t ;
struct x86emu {int dummy; } ;

/* Variables and functions */
 scalar_t__ ACCESS_FLAG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CONDITIONAL_SET_FLAG (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  F_CF ; 
 int /*<<< orphan*/  F_OF ; 
 scalar_t__ XOR2 (int) ; 

__attribute__((used)) static uint32_t 
rcl_long(struct x86emu *emu, uint32_t d, uint8_t s)
{
	uint32_t res, cnt, mask, cf;

	res = d;
	if ((cnt = s % 33) != 0) {
		cf = (d >> (32 - cnt)) & 0x1;
		res = (d << cnt) & 0xffffffff;
		mask = (1 << (cnt - 1)) - 1;
		res |= (d >> (33 - cnt)) & mask;
		if (ACCESS_FLAG(F_CF)) {	/* carry flag is set */
			res |= 1 << (cnt - 1);
		}
		CONDITIONAL_SET_FLAG(cf, F_CF);
		CONDITIONAL_SET_FLAG(cnt == 1 && XOR2(cf + ((res >> 30) & 0x2)),
		    F_OF);
	}
	return res;
}