#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int type; int* normal; scalar_t__ signbits; } ;
typedef  TYPE_2__ cplane_t ;
struct TYPE_11__ {scalar_t__ surfaceFlags; TYPE_2__* plane; } ;
typedef  TYPE_3__ cbrushside_t ;
struct TYPE_14__ {int numsides; int /*<<< orphan*/  contents; TYPE_3__* sides; } ;
struct TYPE_9__ {int numLeafBrushes; size_t firstLeafBrush; } ;
struct TYPE_13__ {TYPE_1__ leaf; } ;
struct TYPE_12__ {size_t numPlanes; size_t numBrushes; int numBrushSides; size_t numLeafBrushes; size_t* leafbrushes; TYPE_2__* planes; TYPE_3__* brushsides; TYPE_7__* brushes; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONTENTS_BODY ; 
 int /*<<< orphan*/  SetPlaneSignbits (TYPE_2__*) ; 
 int /*<<< orphan*/  VectorClear (int*) ; 
 TYPE_7__* box_brush ; 
 TYPE_6__ box_model ; 
 TYPE_2__* box_planes ; 
 TYPE_4__ cm ; 

void CM_InitBoxHull (void)
{
	int			i;
	int			side;
	cplane_t	*p;
	cbrushside_t	*s;

	box_planes = &cm.planes[cm.numPlanes];

	box_brush = &cm.brushes[cm.numBrushes];
	box_brush->numsides = 6;
	box_brush->sides = cm.brushsides + cm.numBrushSides;
	box_brush->contents = CONTENTS_BODY;

	box_model.leaf.numLeafBrushes = 1;
//	box_model.leaf.firstLeafBrush = cm.numBrushes;
	box_model.leaf.firstLeafBrush = cm.numLeafBrushes;
	cm.leafbrushes[cm.numLeafBrushes] = cm.numBrushes;

	for (i=0 ; i<6 ; i++)
	{
		side = i&1;

		// brush sides
		s = &cm.brushsides[cm.numBrushSides+i];
		s->plane = 	cm.planes + (cm.numPlanes+i*2+side);
		s->surfaceFlags = 0;

		// planes
		p = &box_planes[i*2];
		p->type = i>>1;
		p->signbits = 0;
		VectorClear (p->normal);
		p->normal[i>>1] = 1;

		p = &box_planes[i*2+1];
		p->type = 3 + (i>>1);
		p->signbits = 0;
		VectorClear (p->normal);
		p->normal[i>>1] = -1;

		SetPlaneSignbits( p );
	}	
}