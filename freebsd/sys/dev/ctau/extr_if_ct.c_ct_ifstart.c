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
struct ifnet {TYPE_1__* if_softc; } ;
struct TYPE_3__ {int /*<<< orphan*/ * bd; } ;
typedef  TYPE_1__ drv_t ;
typedef  int /*<<< orphan*/  bdrv_t ;

/* Variables and functions */
 int /*<<< orphan*/  CT_LOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CT_UNLOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ct_start (TYPE_1__*) ; 

__attribute__((used)) static void ct_ifstart (struct ifnet *ifp)
{
	drv_t *d = ifp->if_softc;
	bdrv_t *bd = d->bd;
	
	CT_LOCK (bd);
	ct_start (d);
	CT_UNLOCK (bd);
}