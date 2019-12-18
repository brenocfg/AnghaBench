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
typedef  scalar_t__ uint32_t ;
struct pll_sc {struct pdiv_table* pdiv_table; } ;
struct pdiv_table {scalar_t__ divider; scalar_t__ value; } ;

/* Variables and functions */
 scalar_t__ ffs (scalar_t__) ; 

__attribute__((used)) static uint32_t
pdiv_to_reg(struct pll_sc *sc, uint32_t p_div)
{
	struct pdiv_table *tbl;

	tbl = sc->pdiv_table;
	if (tbl == NULL)
		return (ffs(p_div) - 1);

	while (tbl->divider != 0) {
		if (p_div <= tbl->divider)
			return (tbl->value);
		tbl++;
	}
	return (0xFFFFFFFF);
}