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
typedef  int qboolean ;
struct TYPE_6__ {TYPE_1__* original; } ;
typedef  TYPE_2__ bspbrush_t ;
struct TYPE_5__ {int contents; } ;

/* Variables and functions */
 int CONTENTS_DETAIL ; 
 int CONTENTS_SOLID ; 

qboolean BrushGE (bspbrush_t *b1, bspbrush_t *b2)
{
#ifdef ME
	if (create_aas)
	{
		if (b1->original->expansionbbox != b2->original->expansionbbox)
		{
			return false;
		} //end if
		//never have something else bite a ladder brush
		//never have a ladder brush bite something else
		if ( (b1->original->contents & CONTENTS_LADDER)
			&& !(b2->original->contents & CONTENTS_LADDER))
		{ 
			return false;
		} //end if
	} //end if
#endif //ME
	// detail brushes never bite structural brushes
	if ( (b1->original->contents & CONTENTS_DETAIL) 
		&& !(b2->original->contents & CONTENTS_DETAIL) )
	{
		return false;
	} //end if
	if (b1->original->contents & CONTENTS_SOLID)
	{
		return true;
	} //end if
	return false;
}