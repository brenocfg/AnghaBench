#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int outputnumber; struct TYPE_5__** split; struct TYPE_5__* merged; } ;
typedef  TYPE_1__ face_t ;
struct TYPE_6__ {int firstleafface; } ;
typedef  TYPE_2__ dleaf_t ;

/* Variables and functions */
 int /*<<< orphan*/  Error (char*) ; 
 int MAX_MAP_LEAFFACES ; 
 int* dleaffaces ; 
 int numfaces ; 
 int numleaffaces ; 

void EmitMarkFace (dleaf_t *leaf_p, face_t *f)
{
	int			i;
	int			facenum;

	while (f->merged)
		f = f->merged;

	if (f->split[0])
	{
		EmitMarkFace (leaf_p, f->split[0]);
		EmitMarkFace (leaf_p, f->split[1]);
		return;
	}

	facenum = f->outputnumber;
	if (facenum == -1)
		return;	// degenerate face

	if (facenum < 0 || facenum >= numfaces)
		Error ("Bad leafface");
	for (i=leaf_p->firstleafface ; i<numleaffaces ; i++)
		if (dleaffaces[i] == facenum)
			break;		// merged out face
	if (i == numleaffaces)
	{
		if (numleaffaces >= MAX_MAP_LEAFFACES)
			Error ("MAX_MAP_LEAFFACES");

		dleaffaces[numleaffaces] =  facenum;
		numleaffaces++;
	}

}