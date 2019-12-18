#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_7__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  character; } ;
typedef  TYPE_1__ VICMD ;
struct TYPE_9__ {int csearchdir; int /*<<< orphan*/  lastckey; } ;
typedef  int /*<<< orphan*/  SCR ;

/* Variables and functions */
#define  CNOTSET 132 
#define  FSEARCH 131 
#define  TSEARCH 130 
 TYPE_7__* VIP (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  abort () ; 
#define  fSEARCH 129 
 int /*<<< orphan*/  noprev (int /*<<< orphan*/ *) ; 
#define  tSEARCH 128 
 int v_chF (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int v_chT (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int v_chf (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int v_cht (int /*<<< orphan*/ *,TYPE_1__*) ; 

int
v_chrepeat(SCR *sp, VICMD *vp)
{
	vp->character = VIP(sp)->lastckey;

	switch (VIP(sp)->csearchdir) {
	case CNOTSET:
		noprev(sp);
		return (1);
	case FSEARCH:
		return (v_chF(sp, vp));
	case fSEARCH:
		return (v_chf(sp, vp));
	case TSEARCH:
		return (v_chT(sp, vp));
	case tSEARCH:
		return (v_cht(sp, vp));
	default:
		abort();
	}
	/* NOTREACHED */
}