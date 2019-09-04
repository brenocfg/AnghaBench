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
struct TYPE_3__ {int faceflags; struct TYPE_3__* l_next; } ;
typedef  TYPE_1__ tmp_face_t ;
struct TYPE_4__ {TYPE_1__* faces; } ;

/* Variables and functions */
 int FACE_GROUND ; 
 int /*<<< orphan*/  qprintf (char*,int) ; 
 TYPE_2__ tmpaasworld ; 

void AAS_PrintNumGroundFaces(void)
{
	tmp_face_t *tmpface;
	int numgroundfaces = 0;

	for (tmpface = tmpaasworld.faces; tmpface; tmpface = tmpface->l_next)
	{
		if (tmpface->faceflags & FACE_GROUND)
		{
			numgroundfaces++;
		} //end if
	} //end for
	qprintf("%6d ground faces\n", numgroundfaces);
}