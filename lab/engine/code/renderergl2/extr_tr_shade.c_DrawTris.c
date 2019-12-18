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
typedef  int /*<<< orphan*/  vec4_t ;
typedef  int /*<<< orphan*/  shaderProgram_t ;
struct TYPE_5__ {int /*<<< orphan*/  firstIndex; int /*<<< orphan*/  numIndexes; } ;
typedef  TYPE_1__ shaderCommands_t ;
struct TYPE_7__ {int /*<<< orphan*/  modelviewProjection; } ;
struct TYPE_6__ {int /*<<< orphan*/  textureColorShader; int /*<<< orphan*/  whiteImage; } ;

/* Variables and functions */
 int /*<<< orphan*/  GLSL_BindProgram (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GLSL_SetUniformInt (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GLSL_SetUniformMat4 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GLSL_SetUniformVec4 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int GLS_DEPTHMASK_TRUE ; 
 int GLS_POLYMODE_LINE ; 
 int /*<<< orphan*/  GL_BindToTMU (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GL_State (int) ; 
 int /*<<< orphan*/  R_DrawElements (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TB_COLORMAP ; 
 int /*<<< orphan*/  UNIFORM_ALPHATEST ; 
 int /*<<< orphan*/  UNIFORM_COLOR ; 
 int /*<<< orphan*/  UNIFORM_MODELVIEWPROJECTIONMATRIX ; 
 int /*<<< orphan*/  VectorSet4 (int /*<<< orphan*/ ,int,int,int,int) ; 
 TYPE_3__ glState ; 
 int /*<<< orphan*/  qglDepthRange (int /*<<< orphan*/ ,int) ; 
 TYPE_2__ tr ; 

__attribute__((used)) static void DrawTris (shaderCommands_t *input) {
	GL_BindToTMU( tr.whiteImage, TB_COLORMAP );

	GL_State( GLS_POLYMODE_LINE | GLS_DEPTHMASK_TRUE );
	qglDepthRange( 0, 0 );

	{
		shaderProgram_t *sp = &tr.textureColorShader;
		vec4_t color;

		GLSL_BindProgram(sp);
		
		GLSL_SetUniformMat4(sp, UNIFORM_MODELVIEWPROJECTIONMATRIX, glState.modelviewProjection);
		VectorSet4(color, 1, 1, 1, 1);
		GLSL_SetUniformVec4(sp, UNIFORM_COLOR, color);
		GLSL_SetUniformInt(sp, UNIFORM_ALPHATEST, 0);

		R_DrawElements(input->numIndexes, input->firstIndex);
	}

	qglDepthRange( 0, 1 );
}