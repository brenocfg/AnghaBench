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
struct coltab {char co_char; int co_bit; } ;

/* Variables and functions */
 struct coltab* coltab ; 
 int lastcolmod ; 

int
evalcol(int col)
{
	struct coltab *colp;

	if (col == 0)
		return (lastcolmod);
	for (colp = &coltab[0]; colp->co_char != '\0'; colp++)
		if (colp->co_char == col)
			return (colp->co_bit);
	return (0);
}