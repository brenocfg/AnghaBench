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
 int XOR2 (int) ; 

__attribute__((used)) static uint32_t 
rcr_long(struct x86emu *emu, uint32_t d, uint8_t s)
{
	uint32_t res, cnt;
	uint32_t mask, cf, ocf = 0;

	/* rotate right through carry */
	res = d;
	if ((cnt = s % 33) != 0) {
		if (cnt == 1) {
			cf = d & 0x1;
			ocf = ACCESS_FLAG(F_CF) != 0;
		} else
			cf = (d >> (cnt - 1)) & 0x1;
		mask = (1 << (32 - cnt)) - 1;
		res = (d >> cnt) & mask;
		if (cnt != 1)
			res |= (d << (33 - cnt));
		if (ACCESS_FLAG(F_CF)) {	/* carry flag is set */
			res |= 1 << (32 - cnt);
		}
		CONDITIONAL_SET_FLAG(cf, F_CF);
		if (cnt == 1) {
			CONDITIONAL_SET_FLAG(XOR2(ocf + ((d >> 30) & 0x2)),
			    F_OF);
		}
	}
	return res;
}