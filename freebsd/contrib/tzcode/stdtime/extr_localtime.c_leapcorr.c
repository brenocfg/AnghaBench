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
typedef  scalar_t__ time_t ;
struct state {int leapcnt; struct lsinfo* lsis; } ;
struct lsinfo {scalar_t__ ls_trans; long ls_corr; } ;

/* Variables and functions */
 struct state* lclptr ; 

__attribute__((used)) static long
leapcorr(time_t *timep)
{
	struct state *		sp;
	struct lsinfo *	lp;
	int			i;

	sp = lclptr;
	i = sp->leapcnt;
	while (--i >= 0) {
		lp = &sp->lsis[i];
		if (*timep >= lp->ls_trans)
			return lp->ls_corr;
	}
	return 0;
}