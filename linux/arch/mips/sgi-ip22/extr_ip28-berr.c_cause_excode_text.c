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

/* Variables and functions */

__attribute__((used)) static inline const char *cause_excode_text(int cause)
{
	static const char *txt[32] =
	{	"Interrupt",
		"TLB modification",
		"TLB (load or instruction fetch)",
		"TLB (store)",
		"Address error (load or instruction fetch)",
		"Address error (store)",
		"Bus error (instruction fetch)",
		"Bus error (data: load or store)",
		"Syscall",
		"Breakpoint",
		"Reserved instruction",
		"Coprocessor unusable",
		"Arithmetic Overflow",
		"Trap",
		"14",
		"Floating-Point",
		"16", "17", "18", "19", "20", "21", "22",
		"Watch Hi/Lo",
		"24", "25", "26", "27", "28", "29", "30", "31",
	};
	return txt[(cause & 0x7c) >> 2];
}