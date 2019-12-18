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
typedef  scalar_t__ uch ;
struct re_guts {int ncsets; int /*<<< orphan*/  csetsize; scalar_t__* setbits; } ;

/* Variables and functions */
 int CHAR_BIT ; 

__attribute__((used)) static int			/* predicate */
samesets(struct re_guts *g, int c1, int c2)
{
	uch *col;
	int i;
	int ncols = (g->ncsets+(CHAR_BIT-1)) / CHAR_BIT;
	unsigned uc1 = (uch)c1;
	unsigned uc2 = (uch)c2;

	for (i = 0, col = g->setbits; i < ncols; i++, col += g->csetsize)
		if (col[uc1] != col[uc2])
			return(0);
	return(1);
}