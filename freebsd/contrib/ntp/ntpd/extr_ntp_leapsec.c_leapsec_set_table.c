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
typedef  int /*<<< orphan*/  leap_table_t ;

/* Variables and functions */
 int /*<<< orphan*/ * _lptr ; 
 int /*<<< orphan*/ * _ltab ; 

int/*BOOL*/
leapsec_set_table(
	leap_table_t * pt)
{
	if (pt == &_ltab[0] || pt == &_ltab[1])
		_lptr = pt;
	return _lptr == pt;
}