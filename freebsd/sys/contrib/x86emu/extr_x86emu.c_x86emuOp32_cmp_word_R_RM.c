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
struct x86emu {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cmp_long (struct x86emu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  decode_and_fetch_long (struct x86emu*) ; 
 int /*<<< orphan*/ * decode_rh_long_register (struct x86emu*) ; 
 int /*<<< orphan*/  fetch_decode_modrm (struct x86emu*) ; 

__attribute__((used)) static void
x86emuOp32_cmp_word_R_RM(struct x86emu *emu)
{
	uint32_t srcval, *destreg;

	fetch_decode_modrm(emu);
	destreg = decode_rh_long_register(emu);
	srcval = decode_and_fetch_long(emu);
	cmp_long(emu, *destreg, srcval);
}