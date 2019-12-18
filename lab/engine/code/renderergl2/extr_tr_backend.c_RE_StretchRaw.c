#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vec4_t ;
typedef  int /*<<< orphan*/  vec2_t ;
typedef  int /*<<< orphan*/  qboolean ;
typedef  int /*<<< orphan*/  byte ;
struct TYPE_14__ {scalar_t__ framePostProcessed; } ;
struct TYPE_13__ {scalar_t__ framebufferObject; } ;
struct TYPE_12__ {int /*<<< orphan*/  modelviewProjection; } ;
struct TYPE_11__ {scalar_t__ integer; } ;
struct TYPE_10__ {int (* Milliseconds ) () ;int /*<<< orphan*/  (* Printf ) (int /*<<< orphan*/ ,char*,int,int,int) ;int /*<<< orphan*/  (* Error ) (int /*<<< orphan*/ ,char*,int,int) ;} ;
struct TYPE_9__ {scalar_t__ numIndexes; } ;
struct TYPE_8__ {int /*<<< orphan*/  textureColorShader; int /*<<< orphan*/ * renderFbo; int /*<<< orphan*/ * scratchImage; int /*<<< orphan*/  registered; } ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_DROP ; 
 int /*<<< orphan*/  FBO_Bind (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GLSL_BindProgram (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GLSL_SetUniformMat4 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GLSL_SetUniformVec4 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GL_BindToTMU (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PRINT_ALL ; 
 int /*<<< orphan*/  RB_EndSurface () ; 
 int /*<<< orphan*/  RB_InstantQuad2 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RB_SetGL2D () ; 
 int /*<<< orphan*/  RE_UploadCinematic (int,int,int,int,int /*<<< orphan*/  const*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  R_IssuePendingRenderCommands () ; 
 int /*<<< orphan*/  TB_COLORMAP ; 
 int /*<<< orphan*/  UNIFORM_COLOR ; 
 int /*<<< orphan*/  UNIFORM_MODELVIEWPROJECTIONMATRIX ; 
 int /*<<< orphan*/  VectorSet2 (int /*<<< orphan*/ ,float,int) ; 
 int /*<<< orphan*/  VectorSet4 (int /*<<< orphan*/ ,int,int,float,float) ; 
 TYPE_7__ backEnd ; 
 int /*<<< orphan*/  colorWhite ; 
 TYPE_6__ glRefConfig ; 
 TYPE_5__ glState ; 
 int /*<<< orphan*/  qglFinish () ; 
 TYPE_4__* r_speeds ; 
 TYPE_3__ ri ; 
 int stub1 () ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,char*,int,int) ; 
 int stub3 () ; 
 int /*<<< orphan*/  stub4 (int /*<<< orphan*/ ,char*,int,int,int) ; 
 TYPE_2__ tess ; 
 TYPE_1__ tr ; 

void RE_StretchRaw (int x, int y, int w, int h, int cols, int rows, const byte *data, int client, qboolean dirty) {
	int			i, j;
	int			start, end;
	vec4_t quadVerts[4];
	vec2_t texCoords[4];

	if ( !tr.registered ) {
		return;
	}
	R_IssuePendingRenderCommands();

	if ( tess.numIndexes ) {
		RB_EndSurface();
	}

	// we definitely want to sync every frame for the cinematics
	qglFinish();

	start = 0;
	if ( r_speeds->integer ) {
		start = ri.Milliseconds();
	}

	// make sure rows and cols are powers of 2
	for ( i = 0 ; ( 1 << i ) < cols ; i++ ) {
	}
	for ( j = 0 ; ( 1 << j ) < rows ; j++ ) {
	}
	if ( ( 1 << i ) != cols || ( 1 << j ) != rows) {
		ri.Error (ERR_DROP, "Draw_StretchRaw: size not a power of 2: %i by %i", cols, rows);
	}

	RE_UploadCinematic (w, h, cols, rows, data, client, dirty);
	GL_BindToTMU(tr.scratchImage[client], TB_COLORMAP);

	if ( r_speeds->integer ) {
		end = ri.Milliseconds();
		ri.Printf( PRINT_ALL, "qglTexSubImage2D %i, %i: %i msec\n", cols, rows, end - start );
	}

	// FIXME: HUGE hack
	if (glRefConfig.framebufferObject)
	{
		FBO_Bind(backEnd.framePostProcessed ? NULL : tr.renderFbo);
	}

	RB_SetGL2D();

	VectorSet4(quadVerts[0], x,     y,     0.0f, 1.0f);
	VectorSet4(quadVerts[1], x + w, y,     0.0f, 1.0f);
	VectorSet4(quadVerts[2], x + w, y + h, 0.0f, 1.0f);
	VectorSet4(quadVerts[3], x,     y + h, 0.0f, 1.0f);

	VectorSet2(texCoords[0], 0.5f / cols,          0.5f / rows);
	VectorSet2(texCoords[1], (cols - 0.5f) / cols, 0.5f / rows);
	VectorSet2(texCoords[2], (cols - 0.5f) / cols, (rows - 0.5f) / rows);
	VectorSet2(texCoords[3], 0.5f / cols,          (rows - 0.5f) / rows);

	GLSL_BindProgram(&tr.textureColorShader);
	
	GLSL_SetUniformMat4(&tr.textureColorShader, UNIFORM_MODELVIEWPROJECTIONMATRIX, glState.modelviewProjection);
	GLSL_SetUniformVec4(&tr.textureColorShader, UNIFORM_COLOR, colorWhite);

	RB_InstantQuad2(quadVerts, texCoords);
}