#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct sppp {int /*<<< orphan*/  (* pp_down ) (struct sppp*) ;} ;
struct TYPE_6__ {TYPE_4__* ifp; } ;
typedef  TYPE_1__ drv_t ;
struct TYPE_9__ {int if_flags; } ;
struct TYPE_8__ {int pp_flags; } ;
struct TYPE_7__ {TYPE_1__* if_softc; } ;

/* Variables and functions */
 int /*<<< orphan*/  CX_DEBUG (TYPE_1__*,char*) ; 
 TYPE_3__* IFP2SP (TYPE_4__*) ; 
 int PP_CISCO ; 
 int PP_FR ; 
 TYPE_2__* SP2IFP (struct sppp*) ; 
 int /*<<< orphan*/  stub1 (struct sppp*) ; 

__attribute__((used)) static void cx_tlf (struct sppp *sp)
{
	drv_t *d = SP2IFP(sp)->if_softc;

	CX_DEBUG (d, ("cx_tlf\n"));
/*	cx_set_dtr (d->chan, 0);*/
/*	cx_set_rts (d->chan, 0);*/
	if (!(IFP2SP(d->ifp)->pp_flags & PP_FR) && !(d->ifp->if_flags & PP_CISCO))
		sp->pp_down (sp);
}