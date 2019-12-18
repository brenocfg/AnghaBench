#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_7__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vec3_t ;
typedef  scalar_t__ qboolean ;
struct TYPE_8__ {scalar_t__ dist; int /*<<< orphan*/  normal; } ;
typedef  TYPE_1__ bspPlane_t ;
struct TYPE_9__ {int cluster; size_t firstBSPLeafBrush; int numBSPLeafBrushes; } ;
typedef  TYPE_2__ bspLeaf_t ;
struct TYPE_10__ {int numSides; int firstSide; } ;
typedef  TYPE_3__ bspBrush_t ;
struct TYPE_11__ {size_t planeNum; } ;

/* Variables and functions */
 float DotProduct (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int PointInLeafNum (int /*<<< orphan*/ ) ; 
 TYPE_7__* bspBrushSides ; 
 TYPE_3__* bspBrushes ; 
 int* bspLeafBrushes ; 
 TYPE_2__* bspLeafs ; 
 TYPE_1__* bspPlanes ; 
 int maxOpaqueBrush ; 
 int* opaqueBrushes ; 
 scalar_t__ qfalse ; 
 scalar_t__ qtrue ; 

int ClusterForPointExt( vec3_t point, float epsilon ){
	int i, j, b, leafNum, cluster;
	float dot;
	qboolean inside;
	int             *brushes, numBSPBrushes;
	bspLeaf_t       *leaf;
	bspBrush_t      *brush;
	bspPlane_t      *plane;


	/* get leaf for point */
	leafNum = PointInLeafNum( point );
	if ( leafNum < 0 ) {
		return -1;
	}
	leaf = &bspLeafs[ leafNum ];

	/* get the cluster */
	cluster = leaf->cluster;
	if ( cluster < 0 ) {
		return -1;
	}

	/* transparent leaf, so check point against all brushes in the leaf */
	brushes = &bspLeafBrushes[ leaf->firstBSPLeafBrush ];
	numBSPBrushes = leaf->numBSPLeafBrushes;
	for ( i = 0; i < numBSPBrushes; i++ )
	{
		/* get parts */
		b = brushes[ i ];
		if ( b > maxOpaqueBrush ) {
			continue;
		}
		brush = &bspBrushes[ b ];
		if ( !( opaqueBrushes[ b >> 3 ] & ( 1 << ( b & 7 ) ) ) ) {
			continue;
		}

		/* check point against all planes */
		inside = qtrue;
		for ( j = 0; j < brush->numSides && inside; j++ )
		{
			plane = &bspPlanes[ bspBrushSides[ brush->firstSide + j ].planeNum ];
			dot = DotProduct( point, plane->normal );
			dot -= plane->dist;
			if ( dot > epsilon ) {
				inside = qfalse;
			}
		}

		/* if inside, return bogus cluster */
		if ( inside ) {
			return -1 - b;
		}
	}

	/* if the point made it this far, it's not inside any opaque brushes */
	return cluster;
}