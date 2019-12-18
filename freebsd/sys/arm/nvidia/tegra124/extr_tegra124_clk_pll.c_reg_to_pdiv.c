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
typedef  int uint32_t ;
struct pll_sc {struct pdiv_table* pdiv_table; } ;
struct pdiv_table {int divider; int value; } ;

/* Variables and functions */

__attribute__((used)) static uint32_t
reg_to_pdiv(struct pll_sc *sc, uint32_t reg)
{
	struct pdiv_table *tbl;

	tbl = sc->pdiv_table;
	if (tbl == NULL)
		return (1 << reg);

	while (tbl->divider) {
		if (reg == tbl->value)
			return (tbl->divider);
		tbl++;
	}
	return (0);
}