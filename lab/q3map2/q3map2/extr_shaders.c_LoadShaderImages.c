#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int compileFlags; float* averageColor; int /*<<< orphan*/  color; TYPE_2__* lightImage; TYPE_1__* shaderImage; int /*<<< orphan*/  normalImagePath; int /*<<< orphan*/  shader; int /*<<< orphan*/ * normalImage; int /*<<< orphan*/  lightImagePath; int /*<<< orphan*/  implicitImagePath; int /*<<< orphan*/  editorImagePath; } ;
typedef  TYPE_3__ shaderInfo_t ;
struct TYPE_6__ {int width; int height; scalar_t__* pixels; } ;
struct TYPE_5__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int C_NODRAW ; 
 int /*<<< orphan*/  ColorNormalize (float*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DEFAULT_IMAGE ; 
 void* ImageLoad (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SYS_VRB ; 
 int /*<<< orphan*/  SYS_WRN ; 
 int /*<<< orphan*/  Sys_FPrintf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  VectorClear (float*) ; 
 float VectorLength (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VectorScale (float*,float,float*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ warnImage ; 

__attribute__((used)) static void LoadShaderImages( shaderInfo_t *si ){
	int i, count;
	float color[ 4 ];


	/* nodraw shaders don't need images */
	if ( si->compileFlags & C_NODRAW ) {
		si->shaderImage = ImageLoad( DEFAULT_IMAGE );
	}
	else
	{
		/* try to load editor image first */
		si->shaderImage = ImageLoad( si->editorImagePath );

		/* then try shadername */
		if ( si->shaderImage == NULL ) {
			si->shaderImage = ImageLoad( si->shader );
		}

		/* then try implicit image path (note: new behavior!) */
		if ( si->shaderImage == NULL ) {
			si->shaderImage = ImageLoad( si->implicitImagePath );
		}

		/* then try lightimage (note: new behavior!) */
		if ( si->shaderImage == NULL ) {
			si->shaderImage = ImageLoad( si->lightImagePath );
		}

		/* otherwise, use default image */
		if ( si->shaderImage == NULL ) {
			si->shaderImage = ImageLoad( DEFAULT_IMAGE );
			if ( warnImage && strcmp( si->shader, "noshader" ) ) {
				Sys_FPrintf( SYS_WRN, "WARNING: Couldn't find image for shader %s\n", si->shader );
			}
		}

		/* load light image */
		si->lightImage = ImageLoad( si->lightImagePath );

		/* load normalmap image (ok if this is NULL) */
		si->normalImage = ImageLoad( si->normalImagePath );
		if ( si->normalImage != NULL ) {
			Sys_FPrintf( SYS_VRB, "Shader %s has\n"
								  "    NM %s\n", si->shader, si->normalImagePath );
		}
	}

	/* if no light image, use shader image */
	if ( si->lightImage == NULL ) {
		si->lightImage = ImageLoad( si->shaderImage->name );
	}

	/* create default and average colors */
	count = si->lightImage->width * si->lightImage->height;
	VectorClear( color );
	color[ 3 ] = 0.0f;
	for ( i = 0; i < count; i++ )
	{
		color[ 0 ] += si->lightImage->pixels[ i * 4 + 0 ];
		color[ 1 ] += si->lightImage->pixels[ i * 4 + 1 ];
		color[ 2 ] += si->lightImage->pixels[ i * 4 + 2 ];
		color[ 3 ] += si->lightImage->pixels[ i * 4 + 3 ];
	}

	if ( VectorLength( si->color ) <= 0.0f ) {
		ColorNormalize( color, si->color );
	}
	VectorScale( color, ( 1.0f / count ), si->averageColor );
	si->averageColor[ 3 ] = color[ 3 ] / count;
}