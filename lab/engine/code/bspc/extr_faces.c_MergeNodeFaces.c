#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  normal; } ;
typedef  TYPE_1__ plane_t ;
struct TYPE_10__ {size_t planenum; TYPE_3__* faces; } ;
typedef  TYPE_2__ node_t ;
struct TYPE_11__ {size_t planenum; struct TYPE_11__* next; scalar_t__* split; scalar_t__ merged; } ;
typedef  TYPE_3__ face_t ;

/* Variables and functions */
 TYPE_3__* TryMerge (TYPE_3__*,TYPE_3__*,int /*<<< orphan*/ ) ; 
 TYPE_1__* mapplanes ; 

void MergeNodeFaces (node_t *node)
{
	face_t	*f1, *f2, *end;
	face_t	*merged;
	plane_t	*plane;

	plane = &mapplanes[node->planenum];
	merged = NULL;
	
	for (f1 = node->faces ; f1 ; f1 = f1->next)
	{
		if (f1->merged || f1->split[0] || f1->split[1])
			continue;

		for (f2 = node->faces ; f2 != f1 ; f2=f2->next)
		{
			if (f2->merged || f2->split[0] || f2->split[1])
				continue;

			//IDBUG: always passes the face's node's normal to TryMerge()
			//regardless of which side the face is on. Approximately 50% of
			//the time the face will be on the other side of node, and thus
			//the result of the convex/concave test in TryMergeWinding(),
			//which depends on the normal, is flipped. This causes faces
			//that shouldn't be merged to be merged and faces that
			//should be merged to not be merged. 
			//the following added line fixes this bug
			//thanks to: Alexander Malmberg <alexander@malmberg.org>
			plane = &mapplanes[f1->planenum];
			//
			merged = TryMerge (f1, f2, plane->normal);
			if (!merged)
				continue;

			// add merged to the end of the node face list 
			// so it will be checked against all the faces again
			for (end = node->faces ; end->next ; end = end->next)
			;
			merged->next = NULL;
			end->next = merged;
			break;
		}
	}
}