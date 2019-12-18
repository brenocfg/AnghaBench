#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  double* vec3_t ;
typedef  int /*<<< orphan*/  clipHandle_t ;

/* Variables and functions */
 int /*<<< orphan*/  CM_InlineModel (int) ; 
 int /*<<< orphan*/  CM_ModelBounds (int /*<<< orphan*/ ,double*,double*) ; 
 float RadiusFromBounds (double*,double*) ; 
 int /*<<< orphan*/  VectorClear (double*) ; 
 int /*<<< orphan*/  VectorCopy (double*,double*) ; 

void BotImport_BSPModelMinsMaxsOrigin(int modelnum, vec3_t angles, vec3_t outmins, vec3_t outmaxs, vec3_t origin)
{
	clipHandle_t h;
	vec3_t mins, maxs;
	float max;
	int	i;

	h = CM_InlineModel(modelnum);
	CM_ModelBounds(h, mins, maxs);
	//if the model is rotated
	if ((angles[0] || angles[1] || angles[2]))
	{	// expand for rotation

		max = RadiusFromBounds(mins, maxs);
		for (i = 0; i < 3; i++)
		{
			mins[i] = (mins[i] + maxs[i]) * 0.5 - max;
			maxs[i] = (mins[i] + maxs[i]) * 0.5 + max;
		} //end for
	} //end if
	if (outmins) VectorCopy(mins, outmins);
	if (outmaxs) VectorCopy(maxs, outmaxs);
	if (origin) VectorClear(origin);
}