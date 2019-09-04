#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_2__** next; TYPE_1__** prev; TYPE_4__* frontarea; TYPE_4__* backarea; } ;
typedef  TYPE_3__ tmp_face_t ;
struct TYPE_10__ {TYPE_2__* tmpfaces; } ;
typedef  TYPE_4__ tmp_area_t ;
struct TYPE_8__ {TYPE_1__** prev; TYPE_4__* frontarea; } ;
struct TYPE_7__ {TYPE_2__** next; TYPE_4__* frontarea; } ;

/* Variables and functions */
 int /*<<< orphan*/  Error (char*) ; 

void AAS_RemoveFaceFromArea(tmp_face_t *tmpface, tmp_area_t *tmparea)
{
	int side, prevside, nextside;

	if (tmpface->frontarea != tmparea &&
			tmpface->backarea != tmparea)
	{
		Error("AAS_RemoveFaceFromArea: face not part of the area");
	} //end if
	side = tmpface->frontarea != tmparea;
	if (tmpface->prev[side])
	{
		prevside = tmpface->prev[side]->frontarea != tmparea;
		tmpface->prev[side]->next[prevside] = tmpface->next[side];
	} //end if
	else
	{
		tmparea->tmpfaces = tmpface->next[side];
	} //end else
	if (tmpface->next[side])
	{
		nextside = tmpface->next[side]->frontarea != tmparea;
		tmpface->next[side]->prev[nextside] = tmpface->prev[side];
	} //end if
	//remove the area number from the face depending on the side
	if (side) tmpface->backarea = NULL;
	else tmpface->frontarea = NULL;
	tmpface->prev[side] = NULL;
	tmpface->next[side] = NULL;
}