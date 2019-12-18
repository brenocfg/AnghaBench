#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct sppp {int pp_flags; int /*<<< orphan*/  (* pp_up ) (struct sppp*) ;} ;
struct TYPE_6__ {TYPE_1__* ifp; } ;
typedef  TYPE_2__ drv_t ;
struct TYPE_7__ {TYPE_2__* if_softc; } ;
struct TYPE_5__ {int if_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  CT_DEBUG (TYPE_2__*,char*) ; 
 int PP_CISCO ; 
 int PP_FR ; 
 TYPE_3__* SP2IFP (struct sppp*) ; 
 int /*<<< orphan*/  stub1 (struct sppp*) ; 

__attribute__((used)) static void ct_tls (struct sppp *sp)
{
	drv_t *d = SP2IFP(sp)->if_softc;

	CT_DEBUG (d, ("ct_tls\n"));
	if (!(sp->pp_flags & PP_FR) && !(d->ifp->if_flags & PP_CISCO))
		sp->pp_up (sp);
}