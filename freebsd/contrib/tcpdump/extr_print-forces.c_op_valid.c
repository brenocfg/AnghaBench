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
typedef  int uint16_t ;

/* Variables and functions */

__attribute__((used)) static inline int op_valid(uint16_t op, uint16_t mask)
{
	int opb = 1 << (op - 1);

	if (op == 0)
		return 0;
	if (opb & mask)
		return 1;
	/* I guess we should allow vendor operations? */
	if (op >= 0x8000)
		return 1;
	return 0;
}