#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {unsigned int* t_tabstops; } ;
typedef  TYPE_1__ teken_t ;

/* Variables and functions */
 unsigned int T_NUMCOL ; 

__attribute__((used)) static inline int
teken_tab_isset(const teken_t *t, unsigned int col)
{
	unsigned int b, o;

	if (col >= T_NUMCOL)
		return ((col % 8) == 0);

	b = col / (sizeof(unsigned int) * 8);
	o = col % (sizeof(unsigned int) * 8);

	return (t->t_tabstops[b] & (1U << o));
}