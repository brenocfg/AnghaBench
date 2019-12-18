#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xdfenv_t ;
struct TYPE_10__ {scalar_t__ (* hunk_func ) (scalar_t__,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_1__ xdemitconf_t ;
struct TYPE_11__ {int /*<<< orphan*/  priv; } ;
typedef  TYPE_2__ xdemitcb_t ;
struct TYPE_12__ {scalar_t__ i2; scalar_t__ chg2; scalar_t__ i1; scalar_t__ chg1; struct TYPE_12__* next; } ;
typedef  TYPE_3__ xdchange_t ;

/* Variables and functions */
 scalar_t__ stub1 (scalar_t__,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 TYPE_3__* xdl_get_hunk (TYPE_3__**,TYPE_1__ const*) ; 

__attribute__((used)) static int xdl_call_hunk_func(xdfenv_t *xe, xdchange_t *xscr, xdemitcb_t *ecb,
			      xdemitconf_t const *xecfg)
{
	xdchange_t *xch, *xche;

	for (xch = xscr; xch; xch = xche->next) {
		xche = xdl_get_hunk(&xch, xecfg);
		if (!xch)
			break;
		if (xecfg->hunk_func(xch->i1, xche->i1 + xche->chg1 - xch->i1,
				     xch->i2, xche->i2 + xche->chg2 - xch->i2,
				     ecb->priv) < 0)
			return -1;
	}
	return 0;
}