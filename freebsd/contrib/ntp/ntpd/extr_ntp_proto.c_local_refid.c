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
struct peer {scalar_t__ refid; int /*<<< orphan*/  srcadr; TYPE_1__* dstadr; } ;
struct TYPE_3__ {int flags; scalar_t__ addr_refid; } ;
typedef  TYPE_1__ endpt ;

/* Variables and functions */
 int FALSE ; 
 int INT_MCASTIF ; 
 int TRUE ; 
 TYPE_1__* findinterface (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
local_refid(
	struct peer *	p
	)
{
	endpt *	unicast_ep;

	if (p->dstadr != NULL && !(INT_MCASTIF & p->dstadr->flags))
		unicast_ep = p->dstadr;
	else
		unicast_ep = findinterface(&p->srcadr);

	if (unicast_ep != NULL && p->refid == unicast_ep->addr_refid)
		return TRUE;
	else
		return FALSE;
}