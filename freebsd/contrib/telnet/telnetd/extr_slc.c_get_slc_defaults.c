#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ val; int /*<<< orphan*/  flag; } ;
struct TYPE_5__ {int /*<<< orphan*/  val; int /*<<< orphan*/  flag; } ;
struct TYPE_6__ {TYPE_1__ current; int /*<<< orphan*/  sptr; TYPE_2__ defset; } ;

/* Variables and functions */
 int NSLC ; 
 int /*<<< orphan*/  SLC_NOSUPPORT ; 
 int /*<<< orphan*/  init_termbuf () ; 
 TYPE_3__* slctab ; 
 int /*<<< orphan*/  spcset (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void
get_slc_defaults(void)
{
	int i;

	init_termbuf();

	for (i = 1; i <= NSLC; i++) {
		slctab[i].defset.flag =
			spcset(i, &slctab[i].defset.val, &slctab[i].sptr);
		slctab[i].current.flag = SLC_NOSUPPORT;
		slctab[i].current.val = 0;
	}

}