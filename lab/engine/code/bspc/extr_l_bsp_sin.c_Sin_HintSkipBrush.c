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
struct TYPE_6__ {size_t texinfo; } ;
typedef  TYPE_1__ sin_dbrushside_t ;
struct TYPE_7__ {int numsides; int firstside; } ;
typedef  TYPE_2__ sin_dbrush_t ;
struct TYPE_8__ {int flags; } ;

/* Variables and functions */
 int SURF_HINT ; 
 int SURF_SKIP ; 
 TYPE_1__* sin_dbrushsides ; 
 TYPE_3__* sin_texinfo ; 

int Sin_HintSkipBrush(sin_dbrush_t *brush)
{
	int j;
	sin_dbrushside_t *brushside;

	for (j = 0; j < brush->numsides; j++)
	{
		brushside = &sin_dbrushsides[brush->firstside + j];
		if (brushside->texinfo > 0)
		{
			if (sin_texinfo[brushside->texinfo].flags & (SURF_SKIP|SURF_HINT))
			{
				return true;
			} //end if
		} //end if
	} //end for
	return false;
}