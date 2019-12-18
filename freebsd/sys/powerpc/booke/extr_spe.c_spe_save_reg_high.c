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

/* Variables and functions */
 int /*<<< orphan*/  EVSTDW (int) ; 

__attribute__((used)) static uint32_t
spe_save_reg_high(int reg)
{
	uint32_t vec[2];
#define EVSTDW(n)   case n: __asm __volatile ("evstdw %1,0(%0)" \
		:: "b"(vec), "n"(n) : "memory"); break;
	switch (reg) {
	EVSTDW(0);	EVSTDW(1);	EVSTDW(2);	EVSTDW(3);
	EVSTDW(4);	EVSTDW(5);	EVSTDW(6);	EVSTDW(7);
	EVSTDW(8);	EVSTDW(9);	EVSTDW(10);	EVSTDW(11);
	EVSTDW(12);	EVSTDW(13);	EVSTDW(14);	EVSTDW(15);
	EVSTDW(16);	EVSTDW(17);	EVSTDW(18);	EVSTDW(19);
	EVSTDW(20);	EVSTDW(21);	EVSTDW(22);	EVSTDW(23);
	EVSTDW(24);	EVSTDW(25);	EVSTDW(26);	EVSTDW(27);
	EVSTDW(28);	EVSTDW(29);	EVSTDW(30);	EVSTDW(31);
	}
#undef EVSTDW

	return (vec[0]);
}