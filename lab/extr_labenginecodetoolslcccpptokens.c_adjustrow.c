#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int lp; int bp; int max; scalar_t__ tp; } ;
typedef  TYPE_1__ Tokenrow ;

/* Variables and functions */
 int /*<<< orphan*/  growtokenrow (TYPE_1__*) ; 
 int /*<<< orphan*/  memmove (scalar_t__,scalar_t__,int) ; 

void
adjustrow(Tokenrow *trp, int nt)
{
	int nby, size;

	if (nt==0)
		return;
	size = (trp->lp - trp->bp) + nt;
	while (size > trp->max)
		growtokenrow(trp);
	/* nby = sizeof(Token) * (trp->lp - trp->tp); */
	nby = (char *)trp->lp - (char *)trp->tp;
	if (nby)
		memmove(trp->tp+nt, trp->tp, nby);
	trp->lp += nt;
}