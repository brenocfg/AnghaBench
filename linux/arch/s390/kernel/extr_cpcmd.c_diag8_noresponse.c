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
typedef  unsigned long addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  cpcmd_buf ; 

__attribute__((used)) static int diag8_noresponse(int cmdlen)
{
	register unsigned long reg2 asm ("2") = (addr_t) cpcmd_buf;
	register unsigned long reg3 asm ("3") = cmdlen;

	asm volatile(
		"	diag	%1,%0,0x8\n"
		: "+d" (reg3) : "d" (reg2) : "cc");
	return reg3;
}