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
typedef  scalar_t__ uint32_t ;
typedef  int qboolean ;
struct TYPE_7__ {scalar_t__ framebufferMultisample; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* Printf ) (int /*<<< orphan*/ ,char*,int) ;} ;
struct TYPE_5__ {int colorFormat; scalar_t__* colorBuffers; int depthFormat; scalar_t__ depthBuffer; int stencilFormat; scalar_t__ stencilBuffer; int packedDepthStencilFormat; scalar_t__ packedDepthStencilBuffer; int /*<<< orphan*/  frameBuffer; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
typedef  scalar_t__ GLenum ;
typedef  TYPE_1__ FBO_t ;

/* Variables and functions */
 int /*<<< orphan*/  GL_COLOR_ATTACHMENT0 ; 
#define  GL_DEPTH24_STENCIL8 146 
 scalar_t__ GL_DEPTH_ATTACHMENT ; 
#define  GL_DEPTH_COMPONENT 145 
#define  GL_DEPTH_COMPONENT16_ARB 144 
#define  GL_DEPTH_COMPONENT24_ARB 143 
#define  GL_DEPTH_COMPONENT32_ARB 142 
#define  GL_DEPTH_STENCIL 141 
 int /*<<< orphan*/  GL_RENDERBUFFER ; 
#define  GL_RGB 140 
#define  GL_RGB16F_ARB 139 
#define  GL_RGB32F_ARB 138 
#define  GL_RGB8 137 
#define  GL_RGBA 136 
#define  GL_RGBA16F_ARB 135 
#define  GL_RGBA32F_ARB 134 
#define  GL_RGBA8 133 
 scalar_t__ GL_STENCIL_ATTACHMENT ; 
#define  GL_STENCIL_INDEX 132 
#define  GL_STENCIL_INDEX1 131 
#define  GL_STENCIL_INDEX16 130 
#define  GL_STENCIL_INDEX4 129 
#define  GL_STENCIL_INDEX8 128 
 int /*<<< orphan*/  PRINT_WARNING ; 
 TYPE_3__ glRefConfig ; 
 int /*<<< orphan*/  qglGenRenderbuffers (int,scalar_t__*) ; 
 int /*<<< orphan*/  qglNamedFramebufferRenderbufferEXT (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  qglNamedRenderbufferStorageEXT (scalar_t__,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qglNamedRenderbufferStorageMultisampleEXT (scalar_t__,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__ ri ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,char*,int) ; 

void FBO_CreateBuffer(FBO_t *fbo, int format, int index, int multisample)
{
	uint32_t *pRenderBuffer;
	GLenum attachment;
	qboolean absent;

	switch(format)
	{
		case GL_RGB:
		case GL_RGBA:
		case GL_RGB8:
		case GL_RGBA8:
		case GL_RGB16F_ARB:
		case GL_RGBA16F_ARB:
		case GL_RGB32F_ARB:
		case GL_RGBA32F_ARB:
			fbo->colorFormat = format;
			pRenderBuffer = &fbo->colorBuffers[index];
			attachment = GL_COLOR_ATTACHMENT0 + index;
			break;

		case GL_DEPTH_COMPONENT:
		case GL_DEPTH_COMPONENT16_ARB:
		case GL_DEPTH_COMPONENT24_ARB:
		case GL_DEPTH_COMPONENT32_ARB:
			fbo->depthFormat = format;
			pRenderBuffer = &fbo->depthBuffer;
			attachment = GL_DEPTH_ATTACHMENT;
			break;

		case GL_STENCIL_INDEX:
		case GL_STENCIL_INDEX1:
		case GL_STENCIL_INDEX4:
		case GL_STENCIL_INDEX8:
		case GL_STENCIL_INDEX16:
			fbo->stencilFormat = format;
			pRenderBuffer = &fbo->stencilBuffer;
			attachment = GL_STENCIL_ATTACHMENT;
			break;

		case GL_DEPTH_STENCIL:
		case GL_DEPTH24_STENCIL8:
			fbo->packedDepthStencilFormat = format;
			pRenderBuffer = &fbo->packedDepthStencilBuffer;
			attachment = 0; // special for stencil and depth
			break;

		default:
			ri.Printf(PRINT_WARNING, "FBO_CreateBuffer: invalid format %d\n", format);
			return;
	}

	absent = *pRenderBuffer == 0;
	if (absent)
		qglGenRenderbuffers(1, pRenderBuffer);

	if (multisample && glRefConfig.framebufferMultisample)
		qglNamedRenderbufferStorageMultisampleEXT(*pRenderBuffer, multisample, format, fbo->width, fbo->height);
	else
		qglNamedRenderbufferStorageEXT(*pRenderBuffer, format, fbo->width, fbo->height);

	if(absent)
	{
		if (attachment == 0)
		{
			qglNamedFramebufferRenderbufferEXT(fbo->frameBuffer, GL_DEPTH_ATTACHMENT,   GL_RENDERBUFFER, *pRenderBuffer);
			qglNamedFramebufferRenderbufferEXT(fbo->frameBuffer, GL_STENCIL_ATTACHMENT, GL_RENDERBUFFER, *pRenderBuffer);
		}
		else
		{
			qglNamedFramebufferRenderbufferEXT(fbo->frameBuffer, attachment, GL_RENDERBUFFER, *pRenderBuffer);
		}
	}
}