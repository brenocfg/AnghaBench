#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  float* vec4_t ;
typedef  float* ivec4_t ;
struct TYPE_13__ {int width; int height; } ;
struct TYPE_12__ {int vidWidth; int vidHeight; } ;
struct TYPE_11__ {TYPE_3__** textureScratchFbo; int /*<<< orphan*/  whiteImage; TYPE_3__** quarterFbo; } ;

/* Variables and functions */
 float Com_Clamp (float,float,float) ; 
 int /*<<< orphan*/  FBO_Blit (TYPE_3__*,float*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,float*,int /*<<< orphan*/ *,float*,int) ; 
 int /*<<< orphan*/  FBO_BlitFromTexture (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,float*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FBO_FastBlit (TYPE_3__*,int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GLS_DEPTHTEST_DISABLE ; 
 int GLS_DSTBLEND_ONE_MINUS_SRC_ALPHA ; 
 int GLS_SRCBLEND_SRC_ALPHA ; 
 int /*<<< orphan*/  GL_COLOR_BUFFER_BIT ; 
 int /*<<< orphan*/  GL_FALSE ; 
 int /*<<< orphan*/  GL_LINEAR ; 
 int /*<<< orphan*/  GL_TRUE ; 
 int /*<<< orphan*/  RB_HBlur (TYPE_3__*,TYPE_3__*,float) ; 
 int /*<<< orphan*/  RB_VBlur (TYPE_3__*,TYPE_3__*,float) ; 
 int /*<<< orphan*/  VectorSet4 (float*,int,int,int,int) ; 
 TYPE_2__ glConfig ; 
 int /*<<< orphan*/  qglColorMask (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__ tr ; 

void RB_GaussianBlur(float blur)
{
	//float mul = 1.f;
	float factor = Com_Clamp(0.f, 1.f, blur);

	if (factor <= 0.f)
		return;

	{
		ivec4_t srcBox, dstBox;
		vec4_t color;

		VectorSet4(color, 1, 1, 1, 1);

		// first, downsample the framebuffer
		FBO_FastBlit(NULL, NULL, tr.quarterFbo[0], NULL, GL_COLOR_BUFFER_BIT, GL_LINEAR);
		FBO_FastBlit(tr.quarterFbo[0], NULL, tr.textureScratchFbo[0], NULL, GL_COLOR_BUFFER_BIT, GL_LINEAR);

		// set the alpha channel
		qglColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_TRUE);
		FBO_BlitFromTexture(tr.whiteImage, NULL, NULL, tr.textureScratchFbo[0], NULL, NULL, color, GLS_DEPTHTEST_DISABLE);
		qglColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);

		// blur the tiny buffer horizontally and vertically
		RB_HBlur(tr.textureScratchFbo[0], tr.textureScratchFbo[1], factor);
		RB_VBlur(tr.textureScratchFbo[1], tr.textureScratchFbo[0], factor);

		// finally, merge back to framebuffer
		VectorSet4(srcBox, 0, 0, tr.textureScratchFbo[0]->width, tr.textureScratchFbo[0]->height);
		VectorSet4(dstBox, 0, 0, glConfig.vidWidth,              glConfig.vidHeight);
		color[3] = factor;
		FBO_Blit(tr.textureScratchFbo[0], srcBox, NULL, NULL, dstBox, NULL, color, GLS_SRCBLEND_SRC_ALPHA | GLS_DSTBLEND_ONE_MINUS_SRC_ALPHA);
	}
}