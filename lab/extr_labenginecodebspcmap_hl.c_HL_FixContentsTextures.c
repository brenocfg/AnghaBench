#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ side; int numsides; TYPE_1__* sides; struct TYPE_6__* next; } ;
typedef  TYPE_2__ bspbrush_t ;
struct TYPE_7__ {int /*<<< orphan*/  texture; } ;
struct TYPE_5__ {int texinfo; } ;

/* Variables and functions */
 scalar_t__ CONTENTS_LAVA ; 
 scalar_t__ CONTENTS_SLIME ; 
 scalar_t__ CONTENTS_WATER ; 
 scalar_t__ HL_TextureContents (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Log_Print (char*,scalar_t__) ; 
 int map_numtexinfo ; 
 TYPE_3__* map_texinfo ; 

void HL_FixContentsTextures(bspbrush_t *brushlist)
{
	int i, texinfonum;
	bspbrush_t *brush;

	for (brush = brushlist; brush; brush = brush->next)
	{
		//only fix the textures of water, slime and lava brushes
		if (brush->side != CONTENTS_WATER &&
			brush->side != CONTENTS_SLIME &&
			brush->side != CONTENTS_LAVA) continue;
		//
		for (i = 0; i < brush->numsides; i++)
		{
			texinfonum = brush->sides[i].texinfo;
			if (HL_TextureContents(map_texinfo[texinfonum].texture) == brush->side) break;
		} //end for
		//if no specific contents texture was found
		if (i >= brush->numsides)
		{
			texinfonum = -1;
			for (i = 0; i < map_numtexinfo; i++)
			{
				if (HL_TextureContents(map_texinfo[i].texture) == brush->side)
				{
					texinfonum = i;
					break;
				} //end if
			} //end for
		} //end if
		//
		if (texinfonum >= 0)
		{
			//give all the brush sides this contents texture
			for (i = 0; i < brush->numsides; i++)
			{
				brush->sides[i].texinfo = texinfonum;
			} //end for
		} //end if
		else Log_Print("brush contents %d with wrong textures\n", brush->side);
		//
	} //end for
	/*
	for (brush = brushlist; brush; brush = brush->next)
	{
		//give all the brush sides this contents texture
		for (i = 0; i < brush->numsides; i++)
		{
			if (HL_TextureContents(map_texinfo[texinfonum].texture) != brush->side)
			{
				Error("brush contents %d with wrong contents textures %s\n", brush->side,
							HL_TextureContents(map_texinfo[texinfonum].texture));
			} //end if
		} //end for
	} //end for*/
}