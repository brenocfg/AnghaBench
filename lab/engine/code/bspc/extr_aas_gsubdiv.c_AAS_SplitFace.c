#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  winding_t ;
typedef  int /*<<< orphan*/  vec3_t ;
struct TYPE_6__ {int /*<<< orphan*/  faceflags; int /*<<< orphan*/ * winding; int /*<<< orphan*/  planenum; } ;
typedef  TYPE_1__ tmp_face_t ;

/* Variables and functions */
 TYPE_1__* AAS_AllocTmpFace () ; 
 int /*<<< orphan*/  ClipWindingEpsilon (int /*<<< orphan*/ *,int /*<<< orphan*/ ,float,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  FACECLIP_EPSILON ; 
 int /*<<< orphan*/  FreeWinding (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Log_Write (char*) ; 
 scalar_t__ WindingIsTiny (int /*<<< orphan*/ *) ; 

void AAS_SplitFace(tmp_face_t *face, vec3_t normal, float dist,
							tmp_face_t **frontface, tmp_face_t **backface)
{
	winding_t *frontw, *backw;

	//
	*frontface = *backface = NULL;

	ClipWindingEpsilon(face->winding, normal, dist, FACECLIP_EPSILON, &frontw, &backw);

#ifdef DEBUG
	//
	if (frontw)
	{
		if (WindingIsTiny(frontw))
		{
			Log_Write("AAS_SplitFace: tiny back face\r\n");
			FreeWinding(frontw);
			frontw = NULL;
		} //end if
	} //end if
	if (backw)
	{
		if (WindingIsTiny(backw))
		{
			Log_Write("AAS_SplitFace: tiny back face\r\n");
			FreeWinding(backw);
			backw = NULL;
		} //end if
	} //end if
#endif //DEBUG
	//if the winding was split
	if (frontw)
	{
		//check bounds
		(*frontface) = AAS_AllocTmpFace();
		(*frontface)->planenum = face->planenum;
		(*frontface)->winding = frontw;
		(*frontface)->faceflags = face->faceflags;
	} //end if
	if (backw)
	{
		//check bounds
		(*backface) = AAS_AllocTmpFace();
		(*backface)->planenum = face->planenum;
		(*backface)->winding = backw;
		(*backface)->faceflags = face->faceflags;
	} //end if
}