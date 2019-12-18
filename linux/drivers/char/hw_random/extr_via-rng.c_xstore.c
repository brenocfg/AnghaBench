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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */

__attribute__((used)) static inline u32 xstore(u32 *addr, u32 edx_in)
{
	u32 eax_out;

	asm(".byte 0x0F,0xA7,0xC0 /* xstore %%edi (addr=%0) */"
		: "=m" (*addr), "=a" (eax_out), "+d" (edx_in), "+D" (addr));

	return eax_out;
}