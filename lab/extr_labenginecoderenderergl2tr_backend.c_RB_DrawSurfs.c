#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_44__   TYPE_9__ ;
typedef  struct TYPE_43__   TYPE_8__ ;
typedef  struct TYPE_42__   TYPE_7__ ;
typedef  struct TYPE_41__   TYPE_6__ ;
typedef  struct TYPE_40__   TYPE_5__ ;
typedef  struct TYPE_39__   TYPE_4__ ;
typedef  struct TYPE_38__   TYPE_3__ ;
typedef  struct TYPE_37__   TYPE_2__ ;
typedef  struct TYPE_36__   TYPE_21__ ;
typedef  struct TYPE_35__   TYPE_20__ ;
typedef  struct TYPE_34__   TYPE_1__ ;
typedef  struct TYPE_33__   TYPE_19__ ;
typedef  struct TYPE_32__   TYPE_18__ ;
typedef  struct TYPE_31__   TYPE_17__ ;
typedef  struct TYPE_30__   TYPE_16__ ;
typedef  struct TYPE_29__   TYPE_15__ ;
typedef  struct TYPE_28__   TYPE_14__ ;
typedef  struct TYPE_27__   TYPE_13__ ;
typedef  struct TYPE_26__   TYPE_12__ ;
typedef  struct TYPE_25__   TYPE_11__ ;
typedef  struct TYPE_24__   TYPE_10__ ;

/* Type definitions */
typedef  float* vec4_t ;
typedef  int /*<<< orphan*/  vec3_t ;
typedef  float* vec2_t ;
typedef  int qboolean ;
struct TYPE_37__ {int flags; int zFar; float viewportX; float viewportY; float viewportWidth; float viewportHeight; float fovY; float fovX; scalar_t__ targetFbo; size_t targetFboCubemapIndex; } ;
struct TYPE_34__ {int rdflags; int /*<<< orphan*/ * viewaxis; int /*<<< orphan*/  vieworg; int /*<<< orphan*/ * sunShadowMvp; } ;
struct TYPE_39__ {int /*<<< orphan*/  numDrawSurfs; int /*<<< orphan*/  drawSurfs; TYPE_2__ viewParms; TYPE_1__ refdef; } ;
typedef  TYPE_4__ drawSurfsCommand_t ;
struct TYPE_40__ {TYPE_3__* image; } ;
typedef  TYPE_5__ cubemap_t ;
struct TYPE_44__ {int value; } ;
struct TYPE_43__ {scalar_t__ numIndexes; } ;
struct TYPE_42__ {size_t sunFlareQueryIndex; scalar_t__ renderCubeFbo; TYPE_5__* cubemaps; int /*<<< orphan*/  sunFlareShader; int /*<<< orphan*/ * sunFlareQuery; void** sunFlareQueryActive; TYPE_6__* sunRaysFbo; int /*<<< orphan*/  sunShader; int /*<<< orphan*/ * depthBlurShader; TYPE_21__* hdrDepthImage; TYPE_21__** quarterImage; TYPE_6__* screenSsaoFbo; TYPE_6__** quarterFbo; int /*<<< orphan*/  ssaoShader; TYPE_21__* screenScratchImage; TYPE_6__* screenShadowFbo; TYPE_21__* screenShadowImage; TYPE_6__* screenScratchFbo; int /*<<< orphan*/  shadowmaskShader; TYPE_21__** sunShadowDepthImage; TYPE_21__* renderDepthImage; scalar_t__ hdrDepthFbo; int /*<<< orphan*/ * renderFbo; scalar_t__ msaaResolveFbo; } ;
struct TYPE_41__ {float width; float height; } ;
struct TYPE_38__ {int /*<<< orphan*/  texnum; } ;
struct TYPE_36__ {scalar_t__ height; scalar_t__ width; int /*<<< orphan*/  texnum; } ;
struct TYPE_35__ {TYPE_2__ viewParms; TYPE_1__ refdef; void* depthFill; int /*<<< orphan*/ * colorMask; } ;
struct TYPE_33__ {scalar_t__ vidHeight; scalar_t__ vidWidth; } ;
struct TYPE_32__ {scalar_t__ framebufferObject; scalar_t__ occlusionQuery; scalar_t__ depthClamp; int /*<<< orphan*/  intelGraphics; } ;
struct TYPE_31__ {TYPE_6__* currentFBO; } ;
struct TYPE_30__ {scalar_t__ integer; } ;
struct TYPE_29__ {scalar_t__ integer; } ;
struct TYPE_28__ {scalar_t__ integer; } ;
struct TYPE_27__ {scalar_t__ integer; } ;
struct TYPE_26__ {scalar_t__ integer; } ;
struct TYPE_25__ {scalar_t__ integer; } ;
struct TYPE_24__ {scalar_t__ integer; } ;
typedef  TYPE_6__ FBO_t ;

/* Variables and functions */
 int /*<<< orphan*/  FBO_Bind (TYPE_6__*) ; 
 int /*<<< orphan*/  FBO_BlitFromTexture (TYPE_21__*,float*,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FBO_FastBlit (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GLSL_BindProgram (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GLSL_SetUniformMat4 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GLSL_SetUniformVec3 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GLSL_SetUniformVec4 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,float*) ; 
 int /*<<< orphan*/  GLS_DEPTHTEST_DISABLE ; 
 int /*<<< orphan*/  GL_BindToTMU (TYPE_21__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GL_COLOR_BUFFER_BIT ; 
 int /*<<< orphan*/  GL_DEPTH_BUFFER_BIT ; 
 int /*<<< orphan*/  GL_DEPTH_CLAMP ; 
 int GL_FALSE ; 
 int /*<<< orphan*/  GL_NEAREST ; 
 int /*<<< orphan*/  GL_SAMPLES_PASSED ; 
 int /*<<< orphan*/  GL_State (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GL_TEXTURE_2D ; 
 int /*<<< orphan*/  GL_TEXTURE_CUBE_MAP ; 
 float M_PI ; 
 int /*<<< orphan*/  RB_BeginDrawingView () ; 
 int /*<<< orphan*/  RB_DrawSun (double,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RB_EndSurface () ; 
 int /*<<< orphan*/  RB_InstantQuad2 (float**,float**) ; 
 int /*<<< orphan*/  RB_RenderDrawSurfList (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RB_RenderFlares () ; 
 int /*<<< orphan*/  RB_ShadowFinish () ; 
 int RDF_NOWORLDMODEL ; 
 int /*<<< orphan*/  SetViewportAndScissor () ; 
 int /*<<< orphan*/  TB_COLORMAP ; 
 int /*<<< orphan*/  TB_LIGHTMAP ; 
 int /*<<< orphan*/  TB_SHADOWMAP ; 
 int /*<<< orphan*/  TB_SHADOWMAP2 ; 
 int /*<<< orphan*/  TB_SHADOWMAP3 ; 
 int /*<<< orphan*/  TB_SHADOWMAP4 ; 
 int /*<<< orphan*/  UNIFORM_SHADOWMVP ; 
 int /*<<< orphan*/  UNIFORM_SHADOWMVP2 ; 
 int /*<<< orphan*/  UNIFORM_SHADOWMVP3 ; 
 int /*<<< orphan*/  UNIFORM_SHADOWMVP4 ; 
 int /*<<< orphan*/  UNIFORM_VIEWFORWARD ; 
 int /*<<< orphan*/  UNIFORM_VIEWINFO ; 
 int /*<<< orphan*/  UNIFORM_VIEWLEFT ; 
 int /*<<< orphan*/  UNIFORM_VIEWORIGIN ; 
 int /*<<< orphan*/  UNIFORM_VIEWUP ; 
 int VPF_DEPTHCLAMP ; 
 int VPF_DEPTHSHADOW ; 
 int VPF_USESUNLIGHT ; 
 int /*<<< orphan*/  VectorScale (int /*<<< orphan*/ ,float,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VectorSet4 (float*,int,int,float,int) ; 
 TYPE_20__ backEnd ; 
 TYPE_19__ glConfig ; 
 TYPE_18__ glRefConfig ; 
 TYPE_17__ glState ; 
 void* qfalse ; 
 int /*<<< orphan*/  qglBeginQuery (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qglClear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qglClearColor (float,float,float,float) ; 
 int /*<<< orphan*/  qglColorMask (int,int,int,int) ; 
 int /*<<< orphan*/  qglCopyTextureSubImage2DEXT (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  qglDisable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qglEnable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qglEndQuery (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qglGenerateTextureMipmapEXT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qglScissor (float,float,float,float) ; 
 int /*<<< orphan*/  qglViewport (float,float,float,float) ; 
 void* qtrue ; 
 TYPE_16__* r_depthPrepass ; 
 TYPE_15__* r_drawSun ; 
 TYPE_14__* r_drawSunRays ; 
 TYPE_13__* r_shadowBlur ; 
 TYPE_12__* r_shadowCascadeZFar ; 
 TYPE_11__* r_ssao ; 
 TYPE_10__* r_sunlightMode ; 
 TYPE_9__* r_znear ; 
 float tan (float) ; 
 TYPE_8__ tess ; 
 TYPE_7__ tr ; 

const void	*RB_DrawSurfs( const void *data ) {
	const drawSurfsCommand_t	*cmd;
	qboolean isShadowView;

	// finish any 2D drawing if needed
	if ( tess.numIndexes ) {
		RB_EndSurface();
	}

	cmd = (const drawSurfsCommand_t *)data;

	backEnd.refdef = cmd->refdef;
	backEnd.viewParms = cmd->viewParms;

	isShadowView = !!(backEnd.viewParms.flags & VPF_DEPTHSHADOW);

	// clear the z buffer, set the modelview, etc
	RB_BeginDrawingView ();

	if (glRefConfig.framebufferObject && (backEnd.viewParms.flags & VPF_DEPTHCLAMP) && glRefConfig.depthClamp)
	{
		qglEnable(GL_DEPTH_CLAMP);
	}

	if (glRefConfig.framebufferObject && !(backEnd.refdef.rdflags & RDF_NOWORLDMODEL) && (r_depthPrepass->integer || isShadowView))
	{
		FBO_t *oldFbo = glState.currentFBO;
		vec4_t viewInfo;

		VectorSet4(viewInfo, backEnd.viewParms.zFar / r_znear->value, backEnd.viewParms.zFar, 0.0, 0.0);

		backEnd.depthFill = qtrue;
		qglColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
		RB_RenderDrawSurfList( cmd->drawSurfs, cmd->numDrawSurfs );
		qglColorMask(!backEnd.colorMask[0], !backEnd.colorMask[1], !backEnd.colorMask[2], !backEnd.colorMask[3]);
		backEnd.depthFill = qfalse;

		if (!isShadowView)
		{
			if (tr.msaaResolveFbo)
			{
				// If we're using multisampling, resolve the depth first
				FBO_FastBlit(tr.renderFbo, NULL, tr.msaaResolveFbo, NULL, GL_DEPTH_BUFFER_BIT, GL_NEAREST);
			}
			else if (tr.renderFbo == NULL && tr.renderDepthImage)
			{
				// If we're rendering directly to the screen, copy the depth to a texture
				// This is incredibly slow on Intel Graphics, so just skip it on there
				if (!glRefConfig.intelGraphics)
					qglCopyTextureSubImage2DEXT(tr.renderDepthImage->texnum, GL_TEXTURE_2D, 0, 0, 0, 0, 0, glConfig.vidWidth, glConfig.vidHeight);
			}

			if (tr.hdrDepthFbo)
			{
				// need the depth in a texture we can do GL_LINEAR sampling on, so copy it to an HDR image
				vec4_t srcTexCoords;

				VectorSet4(srcTexCoords, 0.0f, 0.0f, 1.0f, 1.0f);

				FBO_BlitFromTexture(tr.renderDepthImage, srcTexCoords, NULL, tr.hdrDepthFbo, NULL, NULL, NULL, 0);
			}

			if (r_sunlightMode->integer && backEnd.viewParms.flags & VPF_USESUNLIGHT)
			{
				vec4_t quadVerts[4];
				vec2_t texCoords[4];
				vec4_t box;

				FBO_Bind(tr.screenShadowFbo);

				box[0] = backEnd.viewParms.viewportX      * tr.screenShadowFbo->width / (float)glConfig.vidWidth;
				box[1] = backEnd.viewParms.viewportY      * tr.screenShadowFbo->height / (float)glConfig.vidHeight;
				box[2] = backEnd.viewParms.viewportWidth  * tr.screenShadowFbo->width / (float)glConfig.vidWidth;
				box[3] = backEnd.viewParms.viewportHeight * tr.screenShadowFbo->height / (float)glConfig.vidHeight;

				qglViewport(box[0], box[1], box[2], box[3]);
				qglScissor(box[0], box[1], box[2], box[3]);

				box[0] = backEnd.viewParms.viewportX / (float)glConfig.vidWidth;
				box[1] = backEnd.viewParms.viewportY / (float)glConfig.vidHeight;
				box[2] = box[0] + backEnd.viewParms.viewportWidth / (float)glConfig.vidWidth;
				box[3] = box[1] + backEnd.viewParms.viewportHeight / (float)glConfig.vidHeight;

				texCoords[0][0] = box[0]; texCoords[0][1] = box[3];
				texCoords[1][0] = box[2]; texCoords[1][1] = box[3];
				texCoords[2][0] = box[2]; texCoords[2][1] = box[1];
				texCoords[3][0] = box[0]; texCoords[3][1] = box[1];

				box[0] = -1.0f;
				box[1] = -1.0f;
				box[2] = 1.0f;
				box[3] = 1.0f;

				VectorSet4(quadVerts[0], box[0], box[3], 0, 1);
				VectorSet4(quadVerts[1], box[2], box[3], 0, 1);
				VectorSet4(quadVerts[2], box[2], box[1], 0, 1);
				VectorSet4(quadVerts[3], box[0], box[1], 0, 1);

				GL_State(GLS_DEPTHTEST_DISABLE);

				GLSL_BindProgram(&tr.shadowmaskShader);

				GL_BindToTMU(tr.renderDepthImage, TB_COLORMAP);

				if (r_shadowCascadeZFar->integer != 0)
				{
					GL_BindToTMU(tr.sunShadowDepthImage[0], TB_SHADOWMAP);
					GL_BindToTMU(tr.sunShadowDepthImage[1], TB_SHADOWMAP2);
					GL_BindToTMU(tr.sunShadowDepthImage[2], TB_SHADOWMAP3);
					GL_BindToTMU(tr.sunShadowDepthImage[3], TB_SHADOWMAP4);

					GLSL_SetUniformMat4(&tr.shadowmaskShader, UNIFORM_SHADOWMVP, backEnd.refdef.sunShadowMvp[0]);
					GLSL_SetUniformMat4(&tr.shadowmaskShader, UNIFORM_SHADOWMVP2, backEnd.refdef.sunShadowMvp[1]);
					GLSL_SetUniformMat4(&tr.shadowmaskShader, UNIFORM_SHADOWMVP3, backEnd.refdef.sunShadowMvp[2]);
					GLSL_SetUniformMat4(&tr.shadowmaskShader, UNIFORM_SHADOWMVP4, backEnd.refdef.sunShadowMvp[3]);
				}
				else
				{
					GL_BindToTMU(tr.sunShadowDepthImage[3], TB_SHADOWMAP);
					GLSL_SetUniformMat4(&tr.shadowmaskShader, UNIFORM_SHADOWMVP, backEnd.refdef.sunShadowMvp[3]);
				}

				GLSL_SetUniformVec3(&tr.shadowmaskShader, UNIFORM_VIEWORIGIN, backEnd.refdef.vieworg);
				{
					vec3_t viewVector;

					float zmax = backEnd.viewParms.zFar;
					float ymax = zmax * tan(backEnd.viewParms.fovY * M_PI / 360.0f);
					float xmax = zmax * tan(backEnd.viewParms.fovX * M_PI / 360.0f);

					VectorScale(backEnd.refdef.viewaxis[0], zmax, viewVector);
					GLSL_SetUniformVec3(&tr.shadowmaskShader, UNIFORM_VIEWFORWARD, viewVector);
					VectorScale(backEnd.refdef.viewaxis[1], xmax, viewVector);
					GLSL_SetUniformVec3(&tr.shadowmaskShader, UNIFORM_VIEWLEFT, viewVector);
					VectorScale(backEnd.refdef.viewaxis[2], ymax, viewVector);
					GLSL_SetUniformVec3(&tr.shadowmaskShader, UNIFORM_VIEWUP, viewVector);

					GLSL_SetUniformVec4(&tr.shadowmaskShader, UNIFORM_VIEWINFO, viewInfo);
				}

				RB_InstantQuad2(quadVerts, texCoords); //, color, shaderProgram, invTexRes);

				if (r_shadowBlur->integer)
				{
					viewInfo[2] = 1.0f / (float)(tr.screenScratchFbo->width);
					viewInfo[3] = 1.0f / (float)(tr.screenScratchFbo->height);

					FBO_Bind(tr.screenScratchFbo);

					GLSL_BindProgram(&tr.depthBlurShader[0]);

					GL_BindToTMU(tr.screenShadowImage, TB_COLORMAP);
					GL_BindToTMU(tr.hdrDepthImage, TB_LIGHTMAP);

					GLSL_SetUniformVec4(&tr.depthBlurShader[0], UNIFORM_VIEWINFO, viewInfo);

					RB_InstantQuad2(quadVerts, texCoords);

					FBO_Bind(tr.screenShadowFbo);

					GLSL_BindProgram(&tr.depthBlurShader[1]);

					GL_BindToTMU(tr.screenScratchImage, TB_COLORMAP);
					GL_BindToTMU(tr.hdrDepthImage, TB_LIGHTMAP);

					GLSL_SetUniformVec4(&tr.depthBlurShader[1], UNIFORM_VIEWINFO, viewInfo);

					RB_InstantQuad2(quadVerts, texCoords);
				}
			}

			if (r_ssao->integer)
			{
				vec4_t quadVerts[4];
				vec2_t texCoords[4];

				viewInfo[2] = 1.0f / ((float)(tr.quarterImage[0]->width)  * tan(backEnd.viewParms.fovX * M_PI / 360.0f) * 2.0f);
				viewInfo[3] = 1.0f / ((float)(tr.quarterImage[0]->height) * tan(backEnd.viewParms.fovY * M_PI / 360.0f) * 2.0f);
				viewInfo[3] *= (float)backEnd.viewParms.viewportHeight / (float)backEnd.viewParms.viewportWidth;

				FBO_Bind(tr.quarterFbo[0]);

				qglViewport(0, 0, tr.quarterFbo[0]->width, tr.quarterFbo[0]->height);
				qglScissor(0, 0, tr.quarterFbo[0]->width, tr.quarterFbo[0]->height);

				VectorSet4(quadVerts[0], -1,  1, 0, 1);
				VectorSet4(quadVerts[1],  1,  1, 0, 1);
				VectorSet4(quadVerts[2],  1, -1, 0, 1);
				VectorSet4(quadVerts[3], -1, -1, 0, 1);

				texCoords[0][0] = 0; texCoords[0][1] = 1;
				texCoords[1][0] = 1; texCoords[1][1] = 1;
				texCoords[2][0] = 1; texCoords[2][1] = 0;
				texCoords[3][0] = 0; texCoords[3][1] = 0;

				GL_State( GLS_DEPTHTEST_DISABLE );

				GLSL_BindProgram(&tr.ssaoShader);

				GL_BindToTMU(tr.hdrDepthImage, TB_COLORMAP);

				GLSL_SetUniformVec4(&tr.ssaoShader, UNIFORM_VIEWINFO, viewInfo);

				RB_InstantQuad2(quadVerts, texCoords); //, color, shaderProgram, invTexRes);


				viewInfo[2] = 1.0f / (float)(tr.quarterImage[0]->width);
				viewInfo[3] = 1.0f / (float)(tr.quarterImage[0]->height);

				FBO_Bind(tr.quarterFbo[1]);

				qglViewport(0, 0, tr.quarterFbo[1]->width, tr.quarterFbo[1]->height);
				qglScissor(0, 0, tr.quarterFbo[1]->width, tr.quarterFbo[1]->height);

				GLSL_BindProgram(&tr.depthBlurShader[0]);

				GL_BindToTMU(tr.quarterImage[0],  TB_COLORMAP);
				GL_BindToTMU(tr.hdrDepthImage, TB_LIGHTMAP);

				GLSL_SetUniformVec4(&tr.depthBlurShader[0], UNIFORM_VIEWINFO, viewInfo);

				RB_InstantQuad2(quadVerts, texCoords); //, color, shaderProgram, invTexRes);


				FBO_Bind(tr.screenSsaoFbo);

				qglViewport(0, 0, tr.screenSsaoFbo->width, tr.screenSsaoFbo->height);
				qglScissor(0, 0, tr.screenSsaoFbo->width, tr.screenSsaoFbo->height);

				GLSL_BindProgram(&tr.depthBlurShader[1]);

				GL_BindToTMU(tr.quarterImage[1],  TB_COLORMAP);
				GL_BindToTMU(tr.hdrDepthImage, TB_LIGHTMAP);

				GLSL_SetUniformVec4(&tr.depthBlurShader[1], UNIFORM_VIEWINFO, viewInfo);


				RB_InstantQuad2(quadVerts, texCoords); //, color, shaderProgram, invTexRes);
			}
		}

		// reset viewport and scissor
		FBO_Bind(oldFbo);
		SetViewportAndScissor();
	}

	if (glRefConfig.framebufferObject && (backEnd.viewParms.flags & VPF_DEPTHCLAMP) && glRefConfig.depthClamp)
	{
		qglDisable(GL_DEPTH_CLAMP);
	}

	if (!isShadowView)
	{
		RB_RenderDrawSurfList( cmd->drawSurfs, cmd->numDrawSurfs );

		if (r_drawSun->integer)
		{
			RB_DrawSun(0.1, tr.sunShader);
		}

		if (glRefConfig.framebufferObject && r_drawSunRays->integer)
		{
			FBO_t *oldFbo = glState.currentFBO;
			FBO_Bind(tr.sunRaysFbo);
			
			qglClearColor( 0.0f, 0.0f, 0.0f, 1.0f );
			qglClear( GL_COLOR_BUFFER_BIT );

			if (glRefConfig.occlusionQuery)
			{
				tr.sunFlareQueryActive[tr.sunFlareQueryIndex] = qtrue;
				qglBeginQuery(GL_SAMPLES_PASSED, tr.sunFlareQuery[tr.sunFlareQueryIndex]);
			}

			RB_DrawSun(0.3, tr.sunFlareShader);

			if (glRefConfig.occlusionQuery)
			{
				qglEndQuery(GL_SAMPLES_PASSED);
			}

			FBO_Bind(oldFbo);
		}

		// darken down any stencil shadows
		RB_ShadowFinish();		

		// add light flares on lights that aren't obscured
		RB_RenderFlares();
	}

	if (glRefConfig.framebufferObject && tr.renderCubeFbo && backEnd.viewParms.targetFbo == tr.renderCubeFbo)
	{
		cubemap_t *cubemap = &tr.cubemaps[backEnd.viewParms.targetFboCubemapIndex];

		FBO_Bind(NULL);
		if (cubemap && cubemap->image)
			qglGenerateTextureMipmapEXT(cubemap->image->texnum, GL_TEXTURE_CUBE_MAP);
	}

	return (const void *)(cmd + 1);
}