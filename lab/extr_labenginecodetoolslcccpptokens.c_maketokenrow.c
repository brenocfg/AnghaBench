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
struct TYPE_3__ {int max; int /*<<< orphan*/ * bp; int /*<<< orphan*/ * lp; int /*<<< orphan*/ * tp; } ;
typedef  TYPE_1__ Tokenrow ;
typedef  int /*<<< orphan*/  Token ;

/* Variables and functions */
 scalar_t__ domalloc (int) ; 

void
maketokenrow(int size, Tokenrow *trp)
{
	trp->max = size;
	if (size>0)
		trp->bp = (Token *)domalloc(size*sizeof(Token));
	else
		trp->bp = NULL;
	trp->tp = trp->bp;
	trp->lp = trp->bp;
}