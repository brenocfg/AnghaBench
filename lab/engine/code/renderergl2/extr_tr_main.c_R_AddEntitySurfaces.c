#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  integer; } ;
struct TYPE_4__ {int num_entities; } ;
struct TYPE_5__ {TYPE_1__ refdef; } ;

/* Variables and functions */
 int /*<<< orphan*/  R_AddEntitySurface (int) ; 
 TYPE_3__* r_drawentities ; 
 TYPE_2__ tr ; 

void R_AddEntitySurfaces (void) {
	int i;

	if ( !r_drawentities->integer ) {
		return;
	}

	for ( i = 0; i < tr.refdef.num_entities; i++)
		R_AddEntitySurface(i);
}