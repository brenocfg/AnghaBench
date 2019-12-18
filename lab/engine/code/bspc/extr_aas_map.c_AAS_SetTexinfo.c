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
struct TYPE_4__ {int flags; scalar_t__ texinfo; } ;
typedef  TYPE_1__ side_t ;
struct TYPE_5__ {int contents; int numsides; TYPE_1__* original_sides; } ;
typedef  TYPE_2__ mapbrush_t ;

/* Variables and functions */
 int CONTENTS_AREAPORTAL ; 
 int CONTENTS_CLUSTERPORTAL ; 
 int CONTENTS_DONOTENTER ; 
 int CONTENTS_JUMPPAD ; 
 int CONTENTS_LADDER ; 
 int CONTENTS_LAVA ; 
 int CONTENTS_PLAYERCLIP ; 
 int CONTENTS_SLIME ; 
 int CONTENTS_TELEPORTER ; 
 int CONTENTS_WATER ; 
 int CONTENTS_WINDOW ; 
 int SFL_BEVEL ; 
 int SFL_TEXTURED ; 
 scalar_t__ TEXINFO_NODE ; 

void AAS_SetTexinfo(mapbrush_t *brush)
{
	int n;
	side_t *side;

	if (brush->contents & (CONTENTS_LADDER
									| CONTENTS_AREAPORTAL
									| CONTENTS_CLUSTERPORTAL
									| CONTENTS_TELEPORTER
									| CONTENTS_JUMPPAD
									| CONTENTS_DONOTENTER
									| CONTENTS_WATER
									| CONTENTS_LAVA
									| CONTENTS_SLIME
									| CONTENTS_WINDOW
									| CONTENTS_PLAYERCLIP))
	{
		//we just set texinfo to 0 because these brush sides MUST be used as
		//bsp splitters textured or not textured
		for (n = 0; n < brush->numsides; n++)
		{
			side = brush->original_sides + n;
			//side->flags |= SFL_TEXTURED|SFL_VISIBLE;
			side->texinfo = 0;
		} //end for
	} //end if
	else
	{
		//only use brush sides as splitters if they are textured
		//texinfo of non-textured sides will be set to TEXINFO_NODE
		for (n = 0; n < brush->numsides; n++)
		{
			side = brush->original_sides + n;
			//don't use side as splitter (set texinfo to TEXINFO_NODE) if not textured
			if (side->flags & (SFL_TEXTURED|SFL_BEVEL)) side->texinfo = 0;
			else side->texinfo = TEXINFO_NODE;
		} //end for
	} //end else
}