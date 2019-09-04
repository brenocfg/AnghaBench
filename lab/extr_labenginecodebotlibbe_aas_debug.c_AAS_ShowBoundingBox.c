#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__* vec3_t ;
struct TYPE_2__ {int (* DebugLineCreate ) () ;int /*<<< orphan*/  (* DebugLineShow ) (int,scalar_t__*,scalar_t__*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  Com_Memcpy (scalar_t__*,scalar_t__*,int) ; 
 int /*<<< orphan*/  LINECOLOR_RED ; 
 int MAX_DEBUGLINES ; 
 TYPE_1__ botimport ; 
 int* debuglines ; 
 scalar_t__* debuglinevisible ; 
 int /*<<< orphan*/  numdebuglines ; 
 scalar_t__ qtrue ; 
 int stub1 () ; 
 int /*<<< orphan*/  stub2 (int,scalar_t__*,scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (int,scalar_t__*,scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (int,scalar_t__*,scalar_t__*,int /*<<< orphan*/ ) ; 

void AAS_ShowBoundingBox(vec3_t origin, vec3_t mins, vec3_t maxs)
{
	vec3_t bboxcorners[8];
	int lines[3];
	int i, j, line;

	//upper corners
	bboxcorners[0][0] = origin[0] + maxs[0];
	bboxcorners[0][1] = origin[1] + maxs[1];
	bboxcorners[0][2] = origin[2] + maxs[2];
	//
	bboxcorners[1][0] = origin[0] + mins[0];
	bboxcorners[1][1] = origin[1] + maxs[1];
	bboxcorners[1][2] = origin[2] + maxs[2];
	//
	bboxcorners[2][0] = origin[0] + mins[0];
	bboxcorners[2][1] = origin[1] + mins[1];
	bboxcorners[2][2] = origin[2] + maxs[2];
	//
	bboxcorners[3][0] = origin[0] + maxs[0];
	bboxcorners[3][1] = origin[1] + mins[1];
	bboxcorners[3][2] = origin[2] + maxs[2];
	//lower corners
	Com_Memcpy(bboxcorners[4], bboxcorners[0], sizeof(vec3_t) * 4);
	for (i = 0; i < 4; i++) bboxcorners[4 + i][2] = origin[2] + mins[2];
	//draw bounding box
	for (i = 0; i < 4; i++)
	{
		for (j = 0, line = 0; j < 3 && line < MAX_DEBUGLINES; line++)
		{
			if (!debuglines[line])
			{
				debuglines[line] = botimport.DebugLineCreate();
				lines[j++] = debuglines[line];
				debuglinevisible[line] = qtrue;
				numdebuglines++;
			} //end if
			else if (!debuglinevisible[line])
			{
				lines[j++] = debuglines[line];
				debuglinevisible[line] = qtrue;
			} //end else
		} //end for
		//top plane
		botimport.DebugLineShow(lines[0], bboxcorners[i],
									bboxcorners[(i+1)&3], LINECOLOR_RED);
		//bottom plane
		botimport.DebugLineShow(lines[1], bboxcorners[4+i],
									bboxcorners[4+((i+1)&3)], LINECOLOR_RED);
		//vertical lines
		botimport.DebugLineShow(lines[2], bboxcorners[i],
									bboxcorners[4+i], LINECOLOR_RED);
	} //end for
}