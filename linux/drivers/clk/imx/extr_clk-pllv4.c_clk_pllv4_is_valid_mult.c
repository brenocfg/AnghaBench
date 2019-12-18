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
 int ARRAY_SIZE (unsigned int*) ; 
 unsigned int* pllv4_mult_table ; 

__attribute__((used)) static bool clk_pllv4_is_valid_mult(unsigned int mult)
{
	int i;

	/* check if mult is in valid MULT table */
	for (i = 0; i < ARRAY_SIZE(pllv4_mult_table); i++) {
		if (pllv4_mult_table[i] == mult)
			return true;
	}

	return false;
}