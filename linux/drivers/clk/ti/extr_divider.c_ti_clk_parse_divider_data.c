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
typedef  int u8 ;
typedef  int u32 ;
struct clk_div_table {int div; int val; } ;

/* Variables and functions */
 int CLKF_INDEX_POWER_OF_TWO ; 
 int CLKF_INDEX_STARTS_AT_ONE ; 
 int ENOMEM ; 
 struct clk_div_table* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int fls (int) ; 
 struct clk_div_table* kcalloc (int,int,int /*<<< orphan*/ ) ; 

int ti_clk_parse_divider_data(int *div_table, int num_dividers, int max_div,
			      u8 flags, u8 *width,
			      const struct clk_div_table **table)
{
	int valid_div = 0;
	u32 val;
	int div;
	int i;
	struct clk_div_table *tmp;

	if (!div_table) {
		if (flags & CLKF_INDEX_STARTS_AT_ONE)
			val = 1;
		else
			val = 0;

		div = 1;

		while (div < max_div) {
			if (flags & CLKF_INDEX_POWER_OF_TWO)
				div <<= 1;
			else
				div++;
			val++;
		}

		*width = fls(val);
		*table = NULL;

		return 0;
	}

	i = 0;

	while (!num_dividers || i < num_dividers) {
		if (div_table[i] == -1)
			break;
		if (div_table[i])
			valid_div++;
		i++;
	}

	num_dividers = i;

	tmp = kcalloc(valid_div + 1, sizeof(*tmp), GFP_KERNEL);
	if (!tmp) {
		*table = ERR_PTR(-ENOMEM);
		return -ENOMEM;
	}

	valid_div = 0;
	*width = 0;

	for (i = 0; i < num_dividers; i++)
		if (div_table[i] > 0) {
			tmp[valid_div].div = div_table[i];
			tmp[valid_div].val = i;
			valid_div++;
			*width = i;
		}

	*width = fls(*width);
	*table = tmp;

	return 0;
}