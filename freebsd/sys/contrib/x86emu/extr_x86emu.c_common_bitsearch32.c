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
typedef  int uint32_t ;
struct x86emu {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONDITIONAL_SET_FLAG (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  F_ZF ; 
 int decode_and_fetch_long (struct x86emu*) ; 
 int* decode_rh_long_register (struct x86emu*) ; 
 int /*<<< orphan*/  fetch_decode_modrm (struct x86emu*) ; 

__attribute__((used)) static void
common_bitsearch32(struct x86emu *emu, int diff)
{
	uint32_t srcval, *dstreg;

	fetch_decode_modrm(emu);
	dstreg = decode_rh_long_register(emu);
	srcval = decode_and_fetch_long(emu);
	CONDITIONAL_SET_FLAG(srcval == 0, F_ZF);
	for (*dstreg = 0; *dstreg < 32; *dstreg += diff) {
		if ((srcval >> *dstreg) & 1)
			break;
	}
}