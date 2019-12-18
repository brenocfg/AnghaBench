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
struct TYPE_6__ {int /*<<< orphan*/  planenum; TYPE_2__* frontarea; struct TYPE_6__** next; } ;
typedef  TYPE_1__ tmp_face_t ;
struct TYPE_7__ {TYPE_1__* tmpfaces; scalar_t__ invalid; struct TYPE_7__* l_next; } ;
typedef  TYPE_2__ tmp_area_t ;
struct TYPE_8__ {TYPE_2__* areas; } ;

/* Variables and functions */
 scalar_t__ AAS_CanMergePlaneFaces (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AAS_MergePlaneFaces (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Log_Write (char*,...) ; 
 int /*<<< orphan*/  qprintf (char*,...) ; 
 TYPE_3__ tmpaasworld ; 

void AAS_MergeAreaPlaneFaces(void)
{
	int num_facemerges = 0;
	int side1;
	tmp_area_t *tmparea, *nexttmparea;
	tmp_face_t *face1;

	Log_Write("AAS_MergePlaneFaces\r\n");
	qprintf("%6d plane face merges", num_facemerges);
	//NOTE: first convex area is a dummy
	for (tmparea = tmpaasworld.areas; tmparea; tmparea = nexttmparea)
	{
		nexttmparea = tmparea->l_next;
		//
		if (tmparea->invalid) continue;
		//
		for (face1 = tmparea->tmpfaces; face1; face1 = face1->next[side1])
		{
			side1 = face1->frontarea != tmparea;
			//
			if (AAS_CanMergePlaneFaces(tmparea, face1->planenum))
			{
				AAS_MergePlaneFaces(tmparea, face1->planenum);
				nexttmparea = tmparea;
				num_facemerges++;
				qprintf("\r%6d", num_facemerges);
				break;
			} //end if
		} //end for
	} //end for
	qprintf("\n");
	Log_Write("%6d plane face merges\r\n", num_facemerges);
}