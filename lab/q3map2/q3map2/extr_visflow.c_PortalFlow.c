#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_7__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ portalvis; void* status; int /*<<< orphan*/  leaf; scalar_t__ portalflood; int /*<<< orphan*/  plane; int /*<<< orphan*/  winding; scalar_t__ removed; } ;
typedef  TYPE_1__ vportal_t ;
struct TYPE_10__ {scalar_t__ mightsee; scalar_t__ depth; int /*<<< orphan*/  portalplane; int /*<<< orphan*/  source; TYPE_1__* portal; } ;
struct TYPE_9__ {int /*<<< orphan*/  c_chains; TYPE_7__ pstack_head; TYPE_1__* base; } ;
typedef  TYPE_2__ threaddata_t ;
typedef  int /*<<< orphan*/  data ;

/* Variables and functions */
 int CountBits (scalar_t__,int) ; 
 int /*<<< orphan*/  RecursiveLeafFlow (int /*<<< orphan*/ ,TYPE_2__*,TYPE_7__*) ; 
 int /*<<< orphan*/  SYS_VRB ; 
 int /*<<< orphan*/  Sys_FPrintf (int /*<<< orphan*/ ,char*,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Sys_Printf (char*,int) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int numportals ; 
 int portallongs ; 
 TYPE_1__* portals ; 
 TYPE_1__** sorted_portals ; 
 void* stat_done ; 
 void* stat_working ; 

void PortalFlow( int portalnum ){
	threaddata_t data;
	int i;
	vportal_t       *p;
	int c_might, c_can;

#ifdef MREDEBUG
	Sys_Printf( "\r%6d", portalnum );
#endif

	p = sorted_portals[portalnum];

	if ( p->removed ) {
		p->status = stat_done;
		return;
	}

	p->status = stat_working;

	c_might = CountBits( p->portalflood, numportals * 2 );

	memset( &data, 0, sizeof( data ) );
	data.base = p;

	data.pstack_head.portal = p;
	data.pstack_head.source = p->winding;
	data.pstack_head.portalplane = p->plane;
	data.pstack_head.depth = 0;
	for ( i = 0 ; i < portallongs ; i++ )
		( (long *)data.pstack_head.mightsee )[i] = ( (long *)p->portalflood )[i];

	RecursiveLeafFlow( p->leaf, &data, &data.pstack_head );

	p->status = stat_done;

	c_can = CountBits( p->portalvis, numportals * 2 );

	Sys_FPrintf( SYS_VRB,"portal:%4i  mightsee:%4i  cansee:%4i (%i chains)\n",
				 (int)( p - portals ), c_might, c_can, data.c_chains );
}