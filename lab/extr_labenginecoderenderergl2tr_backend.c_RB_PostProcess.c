#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_40__   TYPE_9__ ;
typedef  struct TYPE_39__   TYPE_8__ ;
typedef  struct TYPE_38__   TYPE_7__ ;
typedef  struct TYPE_37__   TYPE_6__ ;
typedef  struct TYPE_36__   TYPE_5__ ;
typedef  struct TYPE_35__   TYPE_4__ ;
typedef  struct TYPE_34__   TYPE_3__ ;
typedef  struct TYPE_33__   TYPE_2__ ;
typedef  struct TYPE_32__   TYPE_20__ ;
typedef  struct TYPE_31__   TYPE_1__ ;
typedef  struct TYPE_30__   TYPE_19__ ;
typedef  struct TYPE_29__   TYPE_18__ ;
typedef  struct TYPE_28__   TYPE_17__ ;
typedef  struct TYPE_27__   TYPE_16__ ;
typedef  struct TYPE_26__   TYPE_15__ ;
typedef  struct TYPE_25__   TYPE_14__ ;
typedef  struct TYPE_24__   TYPE_13__ ;
typedef  struct TYPE_23__   TYPE_12__ ;
typedef  struct TYPE_22__   TYPE_11__ ;
typedef  struct TYPE_21__   TYPE_10__ ;

/* Type definitions */
typedef  float* vec4_t ;
typedef  int qboolean ;
struct TYPE_34__ {float viewportX; float viewportY; float viewportWidth; float viewportHeight; } ;
struct TYPE_31__ {int /*<<< orphan*/  blurFactor; } ;
struct TYPE_35__ {TYPE_3__ viewParms; TYPE_1__ refdef; } ;
typedef  TYPE_4__ postProcessCommand_t ;
typedef  float* ivec4_t ;
struct TYPE_40__ {scalar_t__ integer; } ;
struct TYPE_39__ {scalar_t__ integer; } ;
struct TYPE_38__ {scalar_t__ integer; } ;
struct TYPE_37__ {scalar_t__ numIndexes; } ;
struct TYPE_36__ {int /*<<< orphan*/  sunRaysImage; int /*<<< orphan*/  screenShadowImage; int /*<<< orphan*/  renderDepthImage; int /*<<< orphan*/ * pshadowMaps; int /*<<< orphan*/ * sunShadowDepthImage; int /*<<< orphan*/ * screenSsaoFbo; TYPE_2__* screenSsaoImage; int /*<<< orphan*/ * msaaResolveFbo; int /*<<< orphan*/ * renderFbo; } ;
struct TYPE_33__ {float width; float height; } ;
struct TYPE_32__ {int /*<<< orphan*/  framePostProcessed; TYPE_1__ refdef; TYPE_3__ viewParms; } ;
struct TYPE_30__ {scalar_t__ vidHeight; scalar_t__ vidWidth; } ;
struct TYPE_29__ {int /*<<< orphan*/  framebufferObject; } ;
struct TYPE_28__ {scalar_t__ integer; } ;
struct TYPE_27__ {float value; } ;
struct TYPE_26__ {scalar_t__ integer; } ;
struct TYPE_25__ {scalar_t__ integer; } ;
struct TYPE_24__ {scalar_t__ integer; } ;
struct TYPE_23__ {scalar_t__ integer; } ;
struct TYPE_22__ {int /*<<< orphan*/  integer; } ;
struct TYPE_21__ {int integer; } ;
typedef  int /*<<< orphan*/  FBO_t ;

/* Variables and functions */
 int /*<<< orphan*/  FBO_Blit (int /*<<< orphan*/ *,float*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,float*,int /*<<< orphan*/ *,float*,int) ; 
 int /*<<< orphan*/  FBO_BlitFromTexture (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,float*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FBO_FastBlit (int /*<<< orphan*/ *,float*,int /*<<< orphan*/ *,float*,int,int /*<<< orphan*/ ) ; 
 int GLS_DSTBLEND_ZERO ; 
 int GLS_SRCBLEND_DST_COLOR ; 
 int GL_COLOR_BUFFER_BIT ; 
 int GL_DEPTH_BUFFER_BIT ; 
 int /*<<< orphan*/  GL_NEAREST ; 
 int /*<<< orphan*/  RB_BokehBlur (int /*<<< orphan*/ *,float*,int /*<<< orphan*/ *,float*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RB_EndSurface () ; 
 int /*<<< orphan*/  RB_GaussianBlur (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RB_SunRays (int /*<<< orphan*/ *,float*,int /*<<< orphan*/ *,float*) ; 
 int /*<<< orphan*/  RB_ToneMap (int /*<<< orphan*/ *,float*,int /*<<< orphan*/ *,float*,int) ; 
 int /*<<< orphan*/  VectorSet4 (float*,int,scalar_t__,int,int) ; 
 TYPE_20__ backEnd ; 
 TYPE_19__ glConfig ; 
 TYPE_18__ glRefConfig ; 
 float pow (int,float) ; 
 int /*<<< orphan*/  qtrue ; 
 TYPE_17__* r_autoExposure ; 
 TYPE_16__* r_cameraExposure ; 
 TYPE_15__* r_drawSunRays ; 
 TYPE_14__* r_forceAutoExposure ; 
 TYPE_13__* r_forceToneMap ; 
 TYPE_12__* r_hdr ; 
 TYPE_11__* r_postProcess ; 
 TYPE_10__* r_shadows ; 
 TYPE_9__* r_ssao ; 
 TYPE_8__* r_sunlightMode ; 
 TYPE_7__* r_toneMap ; 
 TYPE_6__ tess ; 
 TYPE_5__ tr ; 

const void *RB_PostProcess(const void *data)
{
	const postProcessCommand_t *cmd = data;
	FBO_t *srcFbo;
	ivec4_t srcBox, dstBox;
	qboolean autoExposure;

	// finish any 2D drawing if needed
	if(tess.numIndexes)
		RB_EndSurface();

	if (!glRefConfig.framebufferObject || !r_postProcess->integer)
	{
		// do nothing
		return (const void *)(cmd + 1);
	}

	if (cmd)
	{
		backEnd.refdef = cmd->refdef;
		backEnd.viewParms = cmd->viewParms;
	}

	srcFbo = tr.renderFbo;
	if (tr.msaaResolveFbo)
	{
		// Resolve the MSAA before anything else
		// Can't resolve just part of the MSAA FBO, so multiple views will suffer a performance hit here
		FBO_FastBlit(tr.renderFbo, NULL, tr.msaaResolveFbo, NULL, GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT, GL_NEAREST);
		srcFbo = tr.msaaResolveFbo;
	}

	dstBox[0] = backEnd.viewParms.viewportX;
	dstBox[1] = backEnd.viewParms.viewportY;
	dstBox[2] = backEnd.viewParms.viewportWidth;
	dstBox[3] = backEnd.viewParms.viewportHeight;

	if (r_ssao->integer)
	{
		srcBox[0] = backEnd.viewParms.viewportX      * tr.screenSsaoImage->width  / (float)glConfig.vidWidth;
		srcBox[1] = backEnd.viewParms.viewportY      * tr.screenSsaoImage->height / (float)glConfig.vidHeight;
		srcBox[2] = backEnd.viewParms.viewportWidth  * tr.screenSsaoImage->width  / (float)glConfig.vidWidth;
		srcBox[3] = backEnd.viewParms.viewportHeight * tr.screenSsaoImage->height / (float)glConfig.vidHeight;

		FBO_Blit(tr.screenSsaoFbo, srcBox, NULL, srcFbo, dstBox, NULL, NULL, GLS_SRCBLEND_DST_COLOR | GLS_DSTBLEND_ZERO);
	}

	srcBox[0] = backEnd.viewParms.viewportX;
	srcBox[1] = backEnd.viewParms.viewportY;
	srcBox[2] = backEnd.viewParms.viewportWidth;
	srcBox[3] = backEnd.viewParms.viewportHeight;

	if (srcFbo)
	{
		if (r_hdr->integer && (r_toneMap->integer || r_forceToneMap->integer))
		{
			autoExposure = r_autoExposure->integer || r_forceAutoExposure->integer;
			RB_ToneMap(srcFbo, srcBox, NULL, dstBox, autoExposure);
		}
		else if (r_cameraExposure->value == 0.0f)
		{
			FBO_FastBlit(srcFbo, srcBox, NULL, dstBox, GL_COLOR_BUFFER_BIT, GL_NEAREST);
		}
		else
		{
			vec4_t color;

			color[0] =
			color[1] =
			color[2] = pow(2, r_cameraExposure->value); //exp2(r_cameraExposure->value);
			color[3] = 1.0f;

			FBO_Blit(srcFbo, srcBox, NULL, NULL, dstBox, NULL, color, 0);
		}
	}

	if (r_drawSunRays->integer)
		RB_SunRays(NULL, srcBox, NULL, dstBox);

	if (1)
		RB_BokehBlur(NULL, srcBox, NULL, dstBox, backEnd.refdef.blurFactor);
	else
		RB_GaussianBlur(backEnd.refdef.blurFactor);

#if 0
	if (0)
	{
		vec4_t quadVerts[4];
		vec2_t texCoords[4];
		ivec4_t iQtrBox;
		vec4_t box;
		vec4_t viewInfo;
		static float scale = 5.0f;

		scale -= 0.005f;
		if (scale < 0.01f)
			scale = 5.0f;

		FBO_FastBlit(NULL, NULL, tr.quarterFbo[0], NULL, GL_COLOR_BUFFER_BIT, GL_LINEAR);

		iQtrBox[0] = backEnd.viewParms.viewportX      * tr.quarterImage[0]->width / (float)glConfig.vidWidth;
		iQtrBox[1] = backEnd.viewParms.viewportY      * tr.quarterImage[0]->height / (float)glConfig.vidHeight;
		iQtrBox[2] = backEnd.viewParms.viewportWidth  * tr.quarterImage[0]->width / (float)glConfig.vidWidth;
		iQtrBox[3] = backEnd.viewParms.viewportHeight * tr.quarterImage[0]->height / (float)glConfig.vidHeight;

		qglViewport(iQtrBox[0], iQtrBox[1], iQtrBox[2], iQtrBox[3]);
		qglScissor(iQtrBox[0], iQtrBox[1], iQtrBox[2], iQtrBox[3]);

		VectorSet4(box, 0.0f, 0.0f, 1.0f, 1.0f);

		texCoords[0][0] = box[0]; texCoords[0][1] = box[3];
		texCoords[1][0] = box[2]; texCoords[1][1] = box[3];
		texCoords[2][0] = box[2]; texCoords[2][1] = box[1];
		texCoords[3][0] = box[0]; texCoords[3][1] = box[1];

		VectorSet4(box, -1.0f, -1.0f, 1.0f, 1.0f);

		VectorSet4(quadVerts[0], box[0], box[3], 0, 1);
		VectorSet4(quadVerts[1], box[2], box[3], 0, 1);
		VectorSet4(quadVerts[2], box[2], box[1], 0, 1);
		VectorSet4(quadVerts[3], box[0], box[1], 0, 1);

		GL_State(GLS_DEPTHTEST_DISABLE);


		VectorSet4(viewInfo, backEnd.viewParms.zFar / r_znear->value, backEnd.viewParms.zFar, 0.0, 0.0);

		viewInfo[2] = scale / (float)(tr.quarterImage[0]->width);
		viewInfo[3] = scale / (float)(tr.quarterImage[0]->height);

		FBO_Bind(tr.quarterFbo[1]);
		GLSL_BindProgram(&tr.depthBlurShader[2]);
		GL_BindToTMU(tr.quarterImage[0], TB_COLORMAP);
		GLSL_SetUniformVec4(&tr.depthBlurShader[2], UNIFORM_VIEWINFO, viewInfo);
		RB_InstantQuad2(quadVerts, texCoords);

		FBO_Bind(tr.quarterFbo[0]);
		GLSL_BindProgram(&tr.depthBlurShader[3]);
		GL_BindToTMU(tr.quarterImage[1], TB_COLORMAP);
		GLSL_SetUniformVec4(&tr.depthBlurShader[3], UNIFORM_VIEWINFO, viewInfo);
		RB_InstantQuad2(quadVerts, texCoords);

		SetViewportAndScissor();

		FBO_FastBlit(tr.quarterFbo[1], NULL, NULL, NULL, GL_COLOR_BUFFER_BIT, GL_LINEAR);
		FBO_Bind(NULL);
	}
#endif

	if (0 && r_sunlightMode->integer)
	{
		ivec4_t dstBox;
		VectorSet4(dstBox, 0, glConfig.vidHeight - 128, 128, 128);
		FBO_BlitFromTexture(tr.sunShadowDepthImage[0], NULL, NULL, NULL, dstBox, NULL, NULL, 0);
		VectorSet4(dstBox, 128, glConfig.vidHeight - 128, 128, 128);
		FBO_BlitFromTexture(tr.sunShadowDepthImage[1], NULL, NULL, NULL, dstBox, NULL, NULL, 0);
		VectorSet4(dstBox, 256, glConfig.vidHeight - 128, 128, 128);
		FBO_BlitFromTexture(tr.sunShadowDepthImage[2], NULL, NULL, NULL, dstBox, NULL, NULL, 0);
		VectorSet4(dstBox, 384, glConfig.vidHeight - 128, 128, 128);
		FBO_BlitFromTexture(tr.sunShadowDepthImage[3], NULL, NULL, NULL, dstBox, NULL, NULL, 0);
	}

	if (0 && r_shadows->integer == 4)
	{
		ivec4_t dstBox;
		VectorSet4(dstBox, 512 + 0, glConfig.vidHeight - 128, 128, 128);
		FBO_BlitFromTexture(tr.pshadowMaps[0], NULL, NULL, NULL, dstBox, NULL, NULL, 0);
		VectorSet4(dstBox, 512 + 128, glConfig.vidHeight - 128, 128, 128);
		FBO_BlitFromTexture(tr.pshadowMaps[1], NULL, NULL, NULL, dstBox, NULL, NULL, 0);
		VectorSet4(dstBox, 512 + 256, glConfig.vidHeight - 128, 128, 128);
		FBO_BlitFromTexture(tr.pshadowMaps[2], NULL, NULL, NULL, dstBox, NULL, NULL, 0);
		VectorSet4(dstBox, 512 + 384, glConfig.vidHeight - 128, 128, 128);
		FBO_BlitFromTexture(tr.pshadowMaps[3], NULL, NULL, NULL, dstBox, NULL, NULL, 0);
	}

	if (0)
	{
		ivec4_t dstBox;
		VectorSet4(dstBox, 256, glConfig.vidHeight - 256, 256, 256);
		FBO_BlitFromTexture(tr.renderDepthImage, NULL, NULL, NULL, dstBox, NULL, NULL, 0);
		VectorSet4(dstBox, 512, glConfig.vidHeight - 256, 256, 256);
		FBO_BlitFromTexture(tr.screenShadowImage, NULL, NULL, NULL, dstBox, NULL, NULL, 0);
	}

	if (0)
	{
		ivec4_t dstBox;
		VectorSet4(dstBox, 256, glConfig.vidHeight - 256, 256, 256);
		FBO_BlitFromTexture(tr.sunRaysImage, NULL, NULL, NULL, dstBox, NULL, NULL, 0);
	}

#if 0
	if (r_cubeMapping->integer && tr.numCubemaps)
	{
		ivec4_t dstBox;
		int cubemapIndex = R_CubemapForPoint( backEnd.viewParms.or.origin );

		if (cubemapIndex)
		{
			VectorSet4(dstBox, 0, glConfig.vidHeight - 256, 256, 256);
			//FBO_BlitFromTexture(tr.renderCubeImage, NULL, NULL, NULL, dstBox, &tr.testcubeShader, NULL, 0);
			FBO_BlitFromTexture(tr.cubemaps[cubemapIndex - 1].image, NULL, NULL, NULL, dstBox, &tr.testcubeShader, NULL, 0);
		}
	}
#endif

	backEnd.framePostProcessed = qtrue;

	return (const void *)(cmd + 1);
}