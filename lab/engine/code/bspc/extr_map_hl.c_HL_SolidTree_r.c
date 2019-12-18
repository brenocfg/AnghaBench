#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int contents; } ;
struct TYPE_3__ {int* children; } ;

/* Variables and functions */
#define  HL_CONTENTS_CLIP 142 
#define  HL_CONTENTS_CURRENT_0 141 
#define  HL_CONTENTS_CURRENT_180 140 
#define  HL_CONTENTS_CURRENT_270 139 
#define  HL_CONTENTS_CURRENT_90 138 
#define  HL_CONTENTS_CURRENT_DOWN 137 
#define  HL_CONTENTS_CURRENT_UP 136 
#define  HL_CONTENTS_EMPTY 135 
#define  HL_CONTENTS_LAVA 134 
#define  HL_CONTENTS_ORIGIN 133 
#define  HL_CONTENTS_SKY 132 
#define  HL_CONTENTS_SLIME 131 
#define  HL_CONTENTS_SOLID 130 
#define  HL_CONTENTS_TRANSLUCENT 129 
#define  HL_CONTENTS_WATER 128 
 TYPE_2__* hl_dleafs ; 
 TYPE_1__* hl_dnodes ; 

int HL_SolidTree_r(int nodenum)
{
	if (nodenum < 0)
	{
		switch(hl_dleafs[(-nodenum) - 1].contents)
		{
			case HL_CONTENTS_EMPTY:
			{
				return false;
			} //end case
			case HL_CONTENTS_SOLID:
#ifdef HLCONTENTS
			case HL_CONTENTS_CLIP:
#endif //HLCONTENTS
			case HL_CONTENTS_SKY:
#ifdef HLCONTENTS
			case HL_CONTENTS_TRANSLUCENT:
#endif //HLCONTENTS
			{
				return true;
			} //end case
			case HL_CONTENTS_WATER:
			case HL_CONTENTS_SLIME:
			case HL_CONTENTS_LAVA:
#ifdef HLCONTENTS
			//these contents should not be found in the BSP
			case HL_CONTENTS_ORIGIN:
			case HL_CONTENTS_CURRENT_0:
			case HL_CONTENTS_CURRENT_90:
			case HL_CONTENTS_CURRENT_180:
			case HL_CONTENTS_CURRENT_270:
			case HL_CONTENTS_CURRENT_UP:
			case HL_CONTENTS_CURRENT_DOWN:
#endif //HLCONTENTS
			default:
			{
				return false;
			} //end default
		} //end switch
		return false;
	} //end if
	if (!HL_SolidTree_r(hl_dnodes[nodenum].children[0])) return false;
	if (!HL_SolidTree_r(hl_dnodes[nodenum].children[1])) return false;
	return true;
}