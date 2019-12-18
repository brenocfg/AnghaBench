#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__* vec3_t ;
typedef  int /*<<< orphan*/  shaderProgram_t ;
struct TYPE_8__ {scalar_t__* origin; scalar_t__* oldorigin; } ;
typedef  TYPE_2__ refEntity_t ;
struct TYPE_12__ {TYPE_1__* currentEntity; } ;
struct TYPE_11__ {int /*<<< orphan*/  modelviewProjection; } ;
struct TYPE_10__ {int* indexes; scalar_t__ firstIndex; scalar_t__ numVertexes; scalar_t__ numIndexes; int /*<<< orphan*/ * xyz; } ;
struct TYPE_9__ {int /*<<< orphan*/  whiteImage; int /*<<< orphan*/  textureColorShader; } ;
struct TYPE_7__ {TYPE_2__ e; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATTR_POSITION ; 
 int /*<<< orphan*/  GLSL_BindProgram (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GLSL_SetUniformInt (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GLSL_SetUniformMat4 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GLSL_SetUniformVec4 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int GLS_DSTBLEND_ONE ; 
 int GLS_SRCBLEND_ONE ; 
 int /*<<< orphan*/  GL_BindToTMU (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GL_State (int) ; 
 int NUM_BEAM_SEGS ; 
 int /*<<< orphan*/  PerpendicularVector (scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  RB_UpdateTessVao (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  R_DrawElements (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  RotatePointAroundVector (scalar_t__*,scalar_t__*,scalar_t__*,double) ; 
 int /*<<< orphan*/  TB_COLORMAP ; 
 int /*<<< orphan*/  UNIFORM_ALPHATEST ; 
 int /*<<< orphan*/  UNIFORM_COLOR ; 
 int /*<<< orphan*/  UNIFORM_MODELVIEWPROJECTIONMATRIX ; 
 int /*<<< orphan*/  VectorAdd (scalar_t__*,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  VectorCopy (scalar_t__*,int /*<<< orphan*/ ) ; 
 scalar_t__ VectorNormalize (scalar_t__*) ; 
 int /*<<< orphan*/  VectorScale (scalar_t__*,int,scalar_t__*) ; 
 TYPE_6__ backEnd ; 
 int /*<<< orphan*/  colorRed ; 
 TYPE_5__ glState ; 
 TYPE_4__ tess ; 
 TYPE_3__ tr ; 

__attribute__((used)) static void RB_SurfaceBeam( void )
{
#define NUM_BEAM_SEGS 6
	refEntity_t *e;
	shaderProgram_t *sp = &tr.textureColorShader;
	int	i;
	vec3_t perpvec;
	vec3_t direction, normalized_direction;
	vec3_t	start_points[NUM_BEAM_SEGS], end_points[NUM_BEAM_SEGS];
	vec3_t oldorigin, origin;

	e = &backEnd.currentEntity->e;

	oldorigin[0] = e->oldorigin[0];
	oldorigin[1] = e->oldorigin[1];
	oldorigin[2] = e->oldorigin[2];

	origin[0] = e->origin[0];
	origin[1] = e->origin[1];
	origin[2] = e->origin[2];

	normalized_direction[0] = direction[0] = oldorigin[0] - origin[0];
	normalized_direction[1] = direction[1] = oldorigin[1] - origin[1];
	normalized_direction[2] = direction[2] = oldorigin[2] - origin[2];

	if ( VectorNormalize( normalized_direction ) == 0 )
		return;

	PerpendicularVector( perpvec, normalized_direction );

	VectorScale( perpvec, 4, perpvec );

	for ( i = 0; i < NUM_BEAM_SEGS ; i++ )
	{
		RotatePointAroundVector( start_points[i], normalized_direction, perpvec, (360.0/NUM_BEAM_SEGS)*i );
//		VectorAdd( start_points[i], origin, start_points[i] );
		VectorAdd( start_points[i], direction, end_points[i] );
	}

	GL_BindToTMU( tr.whiteImage, TB_COLORMAP );

	GL_State( GLS_SRCBLEND_ONE | GLS_DSTBLEND_ONE );

	// FIXME: Quake3 doesn't use this, so I never tested it
	tess.numVertexes = 0;
	tess.numIndexes = 0;
	tess.firstIndex = 0;

	for ( i = 0; i <= NUM_BEAM_SEGS; i++ ) {
		VectorCopy(start_points[ i % NUM_BEAM_SEGS ], tess.xyz[tess.numVertexes++]);
		VectorCopy(end_points  [ i % NUM_BEAM_SEGS ], tess.xyz[tess.numVertexes++]);
	}

	for ( i = 0; i < NUM_BEAM_SEGS; i++ ) {
		tess.indexes[tess.numIndexes++] =       i      * 2;
		tess.indexes[tess.numIndexes++] =      (i + 1) * 2;
		tess.indexes[tess.numIndexes++] = 1  +  i      * 2;

		tess.indexes[tess.numIndexes++] = 1  +  i      * 2;
		tess.indexes[tess.numIndexes++] =      (i + 1) * 2;
		tess.indexes[tess.numIndexes++] = 1  + (i + 1) * 2;
	}

	// FIXME: A lot of this can probably be removed for speed, and refactored into a more convenient function
	RB_UpdateTessVao(ATTR_POSITION);
	
	GLSL_BindProgram(sp);
		
	GLSL_SetUniformMat4(sp, UNIFORM_MODELVIEWPROJECTIONMATRIX, glState.modelviewProjection);
					
	GLSL_SetUniformVec4(sp, UNIFORM_COLOR, colorRed);

	GLSL_SetUniformInt(sp, UNIFORM_ALPHATEST, 0);

	R_DrawElements(tess.numIndexes, tess.firstIndex);

	tess.numIndexes = 0;
	tess.numVertexes = 0;
	tess.firstIndex = 0;
}