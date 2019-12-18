#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {size_t leaf; scalar_t__ removed; } ;
typedef  TYPE_1__ vportal_t ;
struct TYPE_5__ {size_t merged; } ;

/* Variables and functions */
 TYPE_3__* leafs ; 
 int numportals ; 
 TYPE_1__* portals ; 

void UpdatePortals( void ){
	int i;
	vportal_t *p;

	for ( i = 0; i < numportals * 2; i++ )
	{
		p = &portals[i];
		if ( p->removed ) {
			continue;
		}
		while ( leafs[p->leaf].merged >= 0 )
			p->leaf = leafs[p->leaf].merged;
	}
}