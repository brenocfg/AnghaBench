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
 int /*<<< orphan*/ * table ; 

void
init_constant_tt(void)
{
    table['-'] = table['+'];
    table['8'] = table['9'];
    table['2'] = table['3'] = table['4'] = table['5'] = table['6'] = table['7'];
    table['A'] = table['C'] = table['D'] = table['c'] = table['d'] = table['a'];
    table['B'] = table['b'];
    table['E'] = table['e'];
    table['U'] = table['u'];
    table['X'] = table['x'];
    table['P'] = table['p'];
    table['F'] = table['f'];
}