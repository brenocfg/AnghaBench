#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_8__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u_long ;
struct TYPE_11__ {int filenum; size_t fieldno; } ;
struct TYPE_10__ {size_t joinf; } ;
struct TYPE_9__ {size_t fieldcnt; } ;
typedef  TYPE_1__ LINE ;
typedef  TYPE_2__ INPUT ;

/* Variables and functions */
 int /*<<< orphan*/  err (int,char*) ; 
 scalar_t__ ferror (int /*<<< orphan*/ ) ; 
 scalar_t__ needsep ; 
 TYPE_8__* olist ; 
 size_t olistcnt ; 
 int /*<<< orphan*/  outfield (TYPE_1__*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  stdout ; 

__attribute__((used)) static void
outtwoline(INPUT *F1, LINE *lp1, INPUT *F2, LINE *lp2)
{
	u_long cnt;

	/* Output a pair of lines according to the join list (if any). */
	if (olist)
		for (cnt = 0; cnt < olistcnt; ++cnt)
			if (olist[cnt].filenum == 0) {
				if (lp1->fieldcnt >= F1->joinf)
					outfield(lp1, F1->joinf, 0);
				else
					outfield(lp2, F2->joinf, 0);
			} else if (olist[cnt].filenum == 1)
				outfield(lp1, olist[cnt].fieldno, 0);
			else /* if (olist[cnt].filenum == 2) */
				outfield(lp2, olist[cnt].fieldno, 0);
	else {
		/*
		 * Output the join field, then the remaining fields from F1
		 * and F2.
		 */
		outfield(lp1, F1->joinf, 0);
		for (cnt = 0; cnt < lp1->fieldcnt; ++cnt)
			if (F1->joinf != cnt)
				outfield(lp1, cnt, 0);
		for (cnt = 0; cnt < lp2->fieldcnt; ++cnt)
			if (F2->joinf != cnt)
				outfield(lp2, cnt, 0);
	}
	(void)printf("\n");
	if (ferror(stdout))
		err(1, "stdout");
	needsep = 0;
}