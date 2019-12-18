#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  va_mask; } ;
struct TYPE_6__ {int /*<<< orphan*/ * xva_rtnattrmap; int /*<<< orphan*/ * xva_rtnattrmapp; TYPE_1__ xva_vattr; int /*<<< orphan*/  xva_magic; int /*<<< orphan*/  xva_mapsize; } ;
typedef  TYPE_2__ xvattr_t ;

/* Variables and functions */
 int /*<<< orphan*/  AT_XVATTR ; 
 int /*<<< orphan*/  XVA_MAGIC ; 
 int /*<<< orphan*/  XVA_MAPSIZE ; 
 int /*<<< orphan*/  bzero (TYPE_2__*,int) ; 

void
xva_init(xvattr_t *xvap)
{
	bzero(xvap, sizeof (xvattr_t));
	xvap->xva_mapsize = XVA_MAPSIZE;
	xvap->xva_magic = XVA_MAGIC;
	xvap->xva_vattr.va_mask = AT_XVATTR;
	xvap->xva_rtnattrmapp = &(xvap->xva_rtnattrmap)[0];
}