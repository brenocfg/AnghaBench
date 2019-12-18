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
 int /*<<< orphan*/  EVLDW (int) ; 

__attribute__((used)) static void
spe_load_reg_high(int reg, uint32_t val)
{
#define	EVLDW(n)   case n: __asm __volatile("evmergelo "#n",%0,"#n \
	    :: "r"(val)); break;
	switch (reg) {
	EVLDW(1);	EVLDW(2);	EVLDW(3);	EVLDW(4);
	EVLDW(5);	EVLDW(6);	EVLDW(7);	EVLDW(8);
	EVLDW(9);	EVLDW(10);	EVLDW(11);	EVLDW(12);
	EVLDW(13);	EVLDW(14);	EVLDW(15);	EVLDW(16);
	EVLDW(17);	EVLDW(18);	EVLDW(19);	EVLDW(20);
	EVLDW(21);	EVLDW(22);	EVLDW(23);	EVLDW(24);
	EVLDW(25);	EVLDW(26);	EVLDW(27);	EVLDW(28);
	EVLDW(29);	EVLDW(30);	EVLDW(31);	EVLDW(0);
	}
#undef EVLDW

}