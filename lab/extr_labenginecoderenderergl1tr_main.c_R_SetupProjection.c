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
struct TYPE_8__ {scalar_t__ stereoFrame; float fovY; float fovX; int* projectionMatrix; scalar_t__ vertFlipBuffer; } ;
typedef  TYPE_2__ viewParms_t ;
typedef  scalar_t__ qboolean ;
struct TYPE_10__ {float value; } ;
struct TYPE_7__ {scalar_t__ vertFlipBuffer; } ;
struct TYPE_9__ {TYPE_1__ refdef; } ;

/* Variables and functions */
 float M_PI ; 
 int /*<<< orphan*/  R_SetupFrustum (TYPE_2__*,float,float,float,float,float) ; 
 scalar_t__ STEREO_LEFT ; 
 scalar_t__ STEREO_RIGHT ; 
 TYPE_4__* r_stereoSeparation ; 
 float tan (float) ; 
 TYPE_3__ tr ; 

void R_SetupProjection(viewParms_t *dest, float zProj, qboolean computeFrustum)
{
	float	xmin, xmax, ymin, ymax;
	float	width, height, stereoSep = r_stereoSeparation->value;

	/*
	 * offset the view origin of the viewer for stereo rendering 
	 * by setting the projection matrix appropriately.
	 */

	if(stereoSep != 0)
	{
		if(dest->stereoFrame == STEREO_LEFT)
			stereoSep = zProj / stereoSep;
		else if(dest->stereoFrame == STEREO_RIGHT)
			stereoSep = zProj / -stereoSep;
		else
			stereoSep = 0;
	}

	ymax = zProj * tan(dest->fovY * M_PI / 360.0f);
	ymin = -ymax;

	xmax = zProj * tan(dest->fovX * M_PI / 360.0f);
	xmin = -xmax;

	width = xmax - xmin;
	height = tr.refdef.vertFlipBuffer ? ymin - ymax : ymax - ymin;

	dest->projectionMatrix[0] = 2 * zProj / width;
	dest->projectionMatrix[4] = 0;
	dest->projectionMatrix[8] = (xmax + xmin + 2 * stereoSep) / width;
	dest->projectionMatrix[12] = 2 * zProj * stereoSep / width;

	dest->projectionMatrix[1] = 0;
	dest->projectionMatrix[5] = 2 * zProj / height;
	dest->projectionMatrix[9] = ( ymax + ymin ) / height;	// normally 0
	dest->projectionMatrix[13] = 0;

	dest->projectionMatrix[3] = 0;
	dest->projectionMatrix[7] = 0;
	dest->projectionMatrix[11] = -1;
	dest->projectionMatrix[15] = 0;

	dest->vertFlipBuffer = tr.refdef.vertFlipBuffer;

	// Now that we have all the data for the projection matrix we can also setup the view frustum.
	if(computeFrustum)
		R_SetupFrustum(dest, xmin, xmax, ymax, zProj, stereoSep);
}