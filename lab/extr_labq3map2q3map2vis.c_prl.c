#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/ * normal; int /*<<< orphan*/  dist; } ;
struct TYPE_6__ {int /*<<< orphan*/  leaf; TYPE_2__ plane; } ;
typedef  TYPE_1__ vportal_t ;
typedef  TYPE_2__ visPlane_t ;
struct TYPE_8__ {int numportals; TYPE_1__** portals; } ;
typedef  TYPE_3__ leaf_t ;

/* Variables and functions */
 int /*<<< orphan*/  Sys_Printf (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* portals ; 

void prl( leaf_t *l ){
	int i;
	vportal_t   *p;
	visPlane_t pl;

	for ( i = 0 ; i < l->numportals ; i++ )
	{
		p = l->portals[i];
		pl = p->plane;
		Sys_Printf( "portal %4i to leaf %4i : %7.1f : (%4.1f, %4.1f, %4.1f)\n",(int)( p - portals ),p->leaf,pl.dist, pl.normal[0], pl.normal[1], pl.normal[2] );
	}
}