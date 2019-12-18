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
struct pmic_table {int address; int reg; int bit; } ;

/* Variables and functions */
 int ENOENT ; 

__attribute__((used)) static int pmic_get_reg_bit(int address, struct pmic_table *table,
			    int count, int *reg, int *bit)
{
	int i;

	for (i = 0; i < count; i++) {
		if (table[i].address == address) {
			*reg = table[i].reg;
			if (bit)
				*bit = table[i].bit;
			return 0;
		}
	}
	return -ENOENT;
}