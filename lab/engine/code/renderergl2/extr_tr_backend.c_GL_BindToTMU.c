#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int flags; int /*<<< orphan*/  texnum; int /*<<< orphan*/  frameUsed; } ;
typedef  TYPE_2__ image_t ;
struct TYPE_9__ {int /*<<< orphan*/  (* Printf ) (int /*<<< orphan*/ ,char*) ;} ;
struct TYPE_8__ {int /*<<< orphan*/  frameCount; TYPE_1__* defaultImage; } ;
struct TYPE_6__ {int /*<<< orphan*/  texnum; } ;
typedef  int /*<<< orphan*/  GLuint ;
typedef  int /*<<< orphan*/  GLenum ;

/* Variables and functions */
 int /*<<< orphan*/  GL_BindMultiTexture (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ GL_TEXTURE0 ; 
 int /*<<< orphan*/  GL_TEXTURE_2D ; 
 int /*<<< orphan*/  GL_TEXTURE_CUBE_MAP ; 
 int IMGFLAG_CUBEMAP ; 
 int /*<<< orphan*/  PRINT_WARNING ; 
 int TB_COLORMAP ; 
 TYPE_4__ ri ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,char*) ; 
 TYPE_3__ tr ; 

void GL_BindToTMU( image_t *image, int tmu )
{
	GLuint texture = (tmu == TB_COLORMAP) ? tr.defaultImage->texnum : 0;
	GLenum target = GL_TEXTURE_2D;

	if (image)
	{
		if (image->flags & IMGFLAG_CUBEMAP)
			target = GL_TEXTURE_CUBE_MAP;

		image->frameUsed = tr.frameCount;
		texture = image->texnum;
	}
	else
	{
		ri.Printf(PRINT_WARNING, "GL_BindToTMU: NULL image\n");
	}

	GL_BindMultiTexture(GL_TEXTURE0 + tmu, target, texture);
}