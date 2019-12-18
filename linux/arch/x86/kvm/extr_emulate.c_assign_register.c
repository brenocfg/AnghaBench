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
typedef  int /*<<< orphan*/  u8 ;
typedef  unsigned long u64 ;
typedef  unsigned long u32 ;
typedef  int /*<<< orphan*/  u16 ;

/* Variables and functions */

__attribute__((used)) static void assign_register(unsigned long *reg, u64 val, int bytes)
{
	/* The 4-byte case *is* correct: in 64-bit mode we zero-extend. */
	switch (bytes) {
	case 1:
		*(u8 *)reg = (u8)val;
		break;
	case 2:
		*(u16 *)reg = (u16)val;
		break;
	case 4:
		*reg = (u32)val;
		break;	/* 64b: zero-extend */
	case 8:
		*reg = val;
		break;
	}
}