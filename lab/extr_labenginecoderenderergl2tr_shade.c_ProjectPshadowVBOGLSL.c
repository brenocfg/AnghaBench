#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_8__ ;
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vec5_t ;
typedef  float* vec4_t ;
typedef  float* vec3_t ;
typedef  int /*<<< orphan*/  shaderProgram_t ;
struct TYPE_11__ {int pshadowBits; scalar_t__ numIndexes; int /*<<< orphan*/  firstIndex; } ;
typedef  TYPE_3__ shaderCommands_t ;
struct TYPE_12__ {float* lightOrigin; float lightRadius; float viewRadius; int /*<<< orphan*/ * lightViewAxis; } ;
typedef  TYPE_4__ pshadow_t ;
struct TYPE_10__ {int /*<<< orphan*/  c_totalIndexes; } ;
struct TYPE_9__ {int num_pshadows; TYPE_4__* pshadows; } ;
struct TYPE_15__ {TYPE_2__ pc; TYPE_1__ refdef; } ;
struct TYPE_14__ {int /*<<< orphan*/  modelviewProjection; } ;
struct TYPE_13__ {int /*<<< orphan*/ * pshadowMaps; int /*<<< orphan*/  pshadowShader; } ;

/* Variables and functions */
 int /*<<< orphan*/  ComputeDeformValues (int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GLSL_BindProgram (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GLSL_SetUniformFloat (int /*<<< orphan*/ *,int /*<<< orphan*/ ,float) ; 
 int /*<<< orphan*/  GLSL_SetUniformInt (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GLSL_SetUniformMat4 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GLSL_SetUniformVec3 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,float*) ; 
 int /*<<< orphan*/  GLSL_SetUniformVec4 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,float*) ; 
 int GLS_DEPTHFUNC_EQUAL ; 
 int GLS_DSTBLEND_ONE_MINUS_SRC_ALPHA ; 
 int GLS_SRCBLEND_SRC_ALPHA ; 
 int /*<<< orphan*/  GL_BindToTMU (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GL_State (int) ; 
 int /*<<< orphan*/  R_DrawElements (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TB_DIFFUSEMAP ; 
 int /*<<< orphan*/  UNIFORM_ALPHATEST ; 
 int /*<<< orphan*/  UNIFORM_LIGHTFORWARD ; 
 int /*<<< orphan*/  UNIFORM_LIGHTORIGIN ; 
 int /*<<< orphan*/  UNIFORM_LIGHTRADIUS ; 
 int /*<<< orphan*/  UNIFORM_LIGHTRIGHT ; 
 int /*<<< orphan*/  UNIFORM_LIGHTUP ; 
 int /*<<< orphan*/  UNIFORM_MODELVIEWPROJECTIONMATRIX ; 
 int /*<<< orphan*/  VectorCopy (float*,float*) ; 
 int /*<<< orphan*/  VectorScale (int /*<<< orphan*/ ,float,float*) ; 
 TYPE_8__ backEnd ; 
 TYPE_7__ glState ; 
 TYPE_3__ tess ; 
 TYPE_5__ tr ; 

__attribute__((used)) static void ProjectPshadowVBOGLSL( void ) {
	int		l;
	vec3_t	origin;
	float	radius;

	int deformGen;
	vec5_t deformParams;

	shaderCommands_t *input = &tess;

	if ( !backEnd.refdef.num_pshadows ) {
		return;
	}
	
	ComputeDeformValues(&deformGen, deformParams);

	for ( l = 0 ; l < backEnd.refdef.num_pshadows ; l++ ) {
		pshadow_t	*ps;
		shaderProgram_t *sp;
		vec4_t vector;

		if ( !( tess.pshadowBits & ( 1 << l ) ) ) {
			continue;	// this surface definitely doesn't have any of this shadow
		}

		ps = &backEnd.refdef.pshadows[l];
		VectorCopy( ps->lightOrigin, origin );
		radius = ps->lightRadius;

		sp = &tr.pshadowShader;

		GLSL_BindProgram(sp);

		GLSL_SetUniformMat4(sp, UNIFORM_MODELVIEWPROJECTIONMATRIX, glState.modelviewProjection);

		VectorCopy(origin, vector);
		vector[3] = 1.0f;
		GLSL_SetUniformVec4(sp, UNIFORM_LIGHTORIGIN, vector);

		VectorScale(ps->lightViewAxis[0], 1.0f / ps->viewRadius, vector);
		GLSL_SetUniformVec3(sp, UNIFORM_LIGHTFORWARD, vector);

		VectorScale(ps->lightViewAxis[1], 1.0f / ps->viewRadius, vector);
		GLSL_SetUniformVec3(sp, UNIFORM_LIGHTRIGHT, vector);

		VectorScale(ps->lightViewAxis[2], 1.0f / ps->viewRadius, vector);
		GLSL_SetUniformVec3(sp, UNIFORM_LIGHTUP, vector);

		GLSL_SetUniformFloat(sp, UNIFORM_LIGHTRADIUS, radius);
	  
		// include GLS_DEPTHFUNC_EQUAL so alpha tested surfaces don't add light
		// where they aren't rendered
		GL_State( GLS_SRCBLEND_SRC_ALPHA | GLS_DSTBLEND_ONE_MINUS_SRC_ALPHA | GLS_DEPTHFUNC_EQUAL );
		GLSL_SetUniformInt(sp, UNIFORM_ALPHATEST, 0);

		GL_BindToTMU( tr.pshadowMaps[l], TB_DIFFUSEMAP );

		//
		// draw
		//

		R_DrawElements(input->numIndexes, input->firstIndex);

		backEnd.pc.c_totalIndexes += tess.numIndexes;
		//backEnd.pc.c_dlightIndexes += tess.numIndexes;
	}
}