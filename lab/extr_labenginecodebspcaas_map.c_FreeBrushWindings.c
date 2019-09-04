#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ winding; } ;
typedef  TYPE_1__ side_t ;
struct TYPE_5__ {int numsides; TYPE_1__* original_sides; } ;
typedef  TYPE_2__ mapbrush_t ;

/* Variables and functions */
 int /*<<< orphan*/  FreeWinding (scalar_t__) ; 

void FreeBrushWindings(mapbrush_t *brush)
{
	int n;
	side_t *side;
	//
	for (n = 0; n < brush->numsides; n++)
	{
		side = brush->original_sides + n;
		//
		if (side->winding) FreeWinding(side->winding);
	} //end for
}