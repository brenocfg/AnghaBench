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
struct TYPE_5__ {int flags; int /*<<< orphan*/  texnum; } ;
typedef  TYPE_1__ image_t ;
struct TYPE_6__ {TYPE_1__** colorImage; int /*<<< orphan*/  frameBuffer; } ;
typedef  int GLuint ;
typedef  int GLenum ;
typedef  TYPE_2__ FBO_t ;

/* Variables and functions */
 int GL_COLOR_ATTACHMENT0 ; 
 int GL_TEXTURE_2D ; 
 int GL_TEXTURE_CUBE_MAP_POSITIVE_X_ARB ; 
 int IMGFLAG_CUBEMAP ; 
 int /*<<< orphan*/  qglNamedFramebufferTexture2DEXT (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void FBO_AttachImage(FBO_t *fbo, image_t *image, GLenum attachment, GLuint cubemapside)
{
	GLenum target = GL_TEXTURE_2D;
	int index;

	if (image->flags & IMGFLAG_CUBEMAP)
		target = GL_TEXTURE_CUBE_MAP_POSITIVE_X_ARB + cubemapside;

	qglNamedFramebufferTexture2DEXT(fbo->frameBuffer, attachment, target, image->texnum, 0);
	index = attachment - GL_COLOR_ATTACHMENT0;
	if (index >= 0 && index <= 15)
		fbo->colorImage[index] = image;
}