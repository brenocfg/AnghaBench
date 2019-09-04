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
typedef  scalar_t__ stereoFrame_t ;
typedef  int /*<<< orphan*/  GLboolean ;

/* Variables and functions */
 int /*<<< orphan*/  GL_FALSE ; 
 int /*<<< orphan*/  GL_TRUE ; 
 int MODE_GREEN_MAGENTA ; 
 int MODE_MAX ; 
 int MODE_RED_BLUE ; 
 int MODE_RED_GREEN ; 
 scalar_t__ STEREO_LEFT ; 
 scalar_t__ STEREO_RIGHT ; 

void R_SetColorMode(GLboolean *rgba, stereoFrame_t stereoFrame, int colormode)
{
	rgba[0] = rgba[1] = rgba[2] = rgba[3] = GL_TRUE;
	
	if(colormode > MODE_MAX)
	{
		if(stereoFrame == STEREO_LEFT)
			stereoFrame = STEREO_RIGHT;
		else if(stereoFrame == STEREO_RIGHT)
			stereoFrame = STEREO_LEFT;
		
		colormode -= MODE_MAX;
	}
	
	if(colormode == MODE_GREEN_MAGENTA)
	{
		if(stereoFrame == STEREO_LEFT)
			rgba[0] = rgba[2] = GL_FALSE;
		else if(stereoFrame == STEREO_RIGHT)
			rgba[1] = GL_FALSE;
	}
	else
	{
		if(stereoFrame == STEREO_LEFT)
			rgba[1] = rgba[2] = GL_FALSE;
		else if(stereoFrame == STEREO_RIGHT)
		{
			rgba[0] = GL_FALSE;
		
			if(colormode == MODE_RED_BLUE)
				rgba[1] = GL_FALSE;
			else if(colormode == MODE_RED_GREEN)
				rgba[2] = GL_FALSE;
		}
	}
}