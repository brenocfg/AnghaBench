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
typedef  int u64 ;
struct tps68470_pmic_table {int reg; int bitmask; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 

__attribute__((used)) static int pmic_get_reg_bit(u64 address,
			    const struct tps68470_pmic_table *table,
			    const unsigned int table_size, int *reg,
			    int *bitmask)
{
	u64 i;

	i = address / 4;
	if (i >= table_size)
		return -ENOENT;

	if (!reg || !bitmask)
		return -EINVAL;

	*reg = table[i].reg;
	*bitmask = table[i].bitmask;

	return 0;
}