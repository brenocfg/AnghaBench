#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;

/* Type definitions */
struct TYPE_20__ {int contents; int leafnum; scalar_t__ expansionbbox; scalar_t__ numsides; } ;
typedef  TYPE_2__ mapbrush_t ;
struct TYPE_21__ {int /*<<< orphan*/  numbrushes; } ;
typedef  TYPE_3__ entity_t ;
struct TYPE_22__ {int numbboxes; TYPE_1__* bboxes; } ;
struct TYPE_19__ {scalar_t__ presencetype; int /*<<< orphan*/  maxs; int /*<<< orphan*/  mins; } ;

/* Variables and functions */
 TYPE_2__* AAS_CopyMapBrush (TYPE_2__*,TYPE_3__*) ; 
 int /*<<< orphan*/  AAS_ExpandMapBrush (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AAS_MakeBrushWindings (TYPE_2__*) ; 
 int /*<<< orphan*/  AAS_PositionBrush (TYPE_3__*,TYPE_2__*) ; 
 int /*<<< orphan*/  AAS_SetTexinfo (TYPE_2__*) ; 
 int /*<<< orphan*/  AAS_ValidEntity (TYPE_3__*) ; 
 int /*<<< orphan*/  AddBrushBevels (TYPE_2__*) ; 
 int CONTENTS_AREAPORTAL ; 
 int CONTENTS_BOTCLIP ; 
 int CONTENTS_CLUSTERPORTAL ; 
 int CONTENTS_DETAIL ; 
 int CONTENTS_DONOTENTER ; 
 int CONTENTS_JUMPPAD ; 
 int CONTENTS_LADDER ; 
 int CONTENTS_LAVA ; 
 int CONTENTS_MOVER ; 
 int CONTENTS_PLAYERCLIP ; 
 int CONTENTS_SLIME ; 
 int CONTENTS_SOLID ; 
 int CONTENTS_TELEPORTER ; 
 int CONTENTS_WATER ; 
 int CONTENTS_WINDOW ; 
 int /*<<< orphan*/  FreeBrushWindings (TYPE_2__*) ; 
 TYPE_5__ cfg ; 
 TYPE_3__* entities ; 
 int /*<<< orphan*/  nummapbrushes ; 
 int /*<<< orphan*/  nummapbrushsides ; 

void AAS_CreateMapBrushes(mapbrush_t *brush, entity_t *mapent, int addbevels)
{
	int i;
	//side_t *s;
	mapbrush_t *bboxbrushes[16];

	//if the brushes are not from an entity used for AAS
	if (!AAS_ValidEntity(mapent))
	{
		nummapbrushsides -= brush->numsides;
		brush->numsides = 0;
		return;
	} //end if
	//
	AAS_PositionBrush(mapent, brush);
	//from all normal solid brushes only the textured brush sides will
	//be used as bsp splitters, so set the right texinfo reference here
	AAS_SetTexinfo(brush);
	//remove contents detail flag, otherwise player clip contents won't be
	//bsped correctly for AAS!
	brush->contents &= ~CONTENTS_DETAIL;
	//if the brush has contents area portal it should be the only contents
	if (brush->contents & (CONTENTS_AREAPORTAL|CONTENTS_CLUSTERPORTAL))
	{
		brush->contents = CONTENTS_CLUSTERPORTAL;
		brush->leafnum = -1;
	} //end if
	//window and playerclip are used for player clipping, make them solid
	if (brush->contents & (CONTENTS_WINDOW | CONTENTS_PLAYERCLIP))
	{
		//
		brush->contents &= ~(CONTENTS_WINDOW | CONTENTS_PLAYERCLIP);
		brush->contents |= CONTENTS_SOLID;
		brush->leafnum = -1;
	} //end if
	//
	if (brush->contents & CONTENTS_BOTCLIP)
	{
		brush->contents = CONTENTS_SOLID;
		brush->leafnum = -1;
	} //end if
	//
	//Log_Write("brush %d contents = ", brush->brushnum);
	//PrintContents(brush->contents);
	//Log_Write("\r\n");
	//if not one of the following brushes then the brush is NOT used for AAS
	if (!(brush->contents & (CONTENTS_SOLID
									| CONTENTS_LADDER
									| CONTENTS_CLUSTERPORTAL
									| CONTENTS_DONOTENTER
									| CONTENTS_TELEPORTER
									| CONTENTS_JUMPPAD
									| CONTENTS_WATER
									| CONTENTS_LAVA
									| CONTENTS_SLIME
									| CONTENTS_MOVER
									)))
	{
		nummapbrushsides -= brush->numsides;
		brush->numsides = 0;
		return;
	} //end if
	//fix the map brush
	//AAS_FixMapBrush(brush);
	//if brush bevels should be added (for real map brushes, not bsp map brushes)
	if (addbevels)
	{
		//NOTE: we first have to get the mins and maxs of the brush before
		//			creating the brush bevels... the mins and maxs are used to
		//			create them. so we call MakeBrushWindings to get the mins
		//			and maxs and then after creating the bevels we free the
		//			windings because they are created for all sides (including
		//			bevels) a little later
		AAS_MakeBrushWindings(brush);
		AddBrushBevels(brush);
		FreeBrushWindings(brush);
	} //end if
	//NOTE: add the brush to the WORLD entity!!!
	mapent = &entities[0];
	//there's at least one new brush for now
	nummapbrushes++;
	mapent->numbrushes++;
	//liquid brushes are expanded for the maximum possible bounding box
	if (brush->contents & (CONTENTS_WATER
									| CONTENTS_LAVA
									| CONTENTS_SLIME 
									| CONTENTS_TELEPORTER
									| CONTENTS_JUMPPAD
									| CONTENTS_DONOTENTER
									| CONTENTS_MOVER
									))
	{
		brush->expansionbbox = 0;
		//NOTE: the first bounding box is the max
		//FIXME: use max bounding box created from all bboxes
		AAS_ExpandMapBrush(brush, cfg.bboxes[0].mins, cfg.bboxes[0].maxs);
		AAS_MakeBrushWindings(brush);
	} //end if
	//area portal brushes are NOT expanded
	else if (brush->contents & CONTENTS_CLUSTERPORTAL)
	{
		brush->expansionbbox = 0;
		//NOTE: the first bounding box is the max
		//FIXME: use max bounding box created from all bboxes
		AAS_ExpandMapBrush(brush, cfg.bboxes[0].mins, cfg.bboxes[0].maxs);
		AAS_MakeBrushWindings(brush);
	} //end if
	//all solid brushes are expanded for all bounding boxes
	else if (brush->contents & (CONTENTS_SOLID
										| CONTENTS_LADDER
										))
	{
		//brush for the first bounding box
		bboxbrushes[0] = brush;
		//make a copy for the other bounding boxes
		for (i = 1; i < cfg.numbboxes; i++)
		{
			bboxbrushes[i] = AAS_CopyMapBrush(brush, mapent);
		} //end for
		//expand every brush for it's bounding box and create windings
		for (i = 0; i < cfg.numbboxes; i++)
		{
			AAS_ExpandMapBrush(bboxbrushes[i], cfg.bboxes[i].mins, cfg.bboxes[i].maxs);
			bboxbrushes[i]->expansionbbox = cfg.bboxes[i].presencetype;
			AAS_MakeBrushWindings(bboxbrushes[i]);
		} //end for
	} //end else
}