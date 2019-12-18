#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ seamlessCubeMap; scalar_t__ vertexArrayObject; scalar_t__ framebufferObject; } ;
struct TYPE_9__ {int glStateBits; scalar_t__ vertexAttribsEnabled; int /*<<< orphan*/ * currentVao; int /*<<< orphan*/  faceCullFront; int /*<<< orphan*/  faceCulling; scalar_t__ storedGlState; } ;
struct TYPE_8__ {int /*<<< orphan*/  value; } ;
struct TYPE_7__ {int /*<<< orphan*/  value; } ;
struct TYPE_6__ {int /*<<< orphan*/  string; } ;

/* Variables and functions */
 int /*<<< orphan*/  CT_TWO_SIDED ; 
 int GLS_DEPTHMASK_TRUE ; 
 int GLS_DEPTHTEST_DISABLE ; 
 int /*<<< orphan*/  GL_ARRAY_BUFFER ; 
 int /*<<< orphan*/  GL_BLEND ; 
 int /*<<< orphan*/  GL_BindNullFramebuffers () ; 
 int /*<<< orphan*/  GL_BindNullProgram () ; 
 int /*<<< orphan*/  GL_BindNullTextures () ; 
 int /*<<< orphan*/  GL_CULL_FACE ; 
 int /*<<< orphan*/  GL_DEPTH_TEST ; 
 int /*<<< orphan*/  GL_ELEMENT_ARRAY_BUFFER ; 
 int /*<<< orphan*/  GL_FILL ; 
 int /*<<< orphan*/  GL_FRONT ; 
 int /*<<< orphan*/  GL_FRONT_AND_BACK ; 
 int /*<<< orphan*/  GL_LEQUAL ; 
 int /*<<< orphan*/  GL_SCISSOR_TEST ; 
 int /*<<< orphan*/  GL_TEXTURE_CUBE_MAP_SEAMLESS ; 
 int /*<<< orphan*/  GL_TRUE ; 
 int /*<<< orphan*/  GL_TextureMode (int /*<<< orphan*/ ) ; 
 TYPE_5__ glRefConfig ; 
 TYPE_4__ glState ; 
 int /*<<< orphan*/  qglBindBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qglBindVertexArray (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qglClearColor (float,float,float,float) ; 
 int /*<<< orphan*/  qglClearDepth (float) ; 
 int /*<<< orphan*/  qglCullFace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qglDepthFunc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qglDepthMask (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qglDisable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qglEnable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qglPolygonMode (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qglPolygonOffset (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__* r_offsetFactor ; 
 TYPE_2__* r_offsetUnits ; 
 TYPE_1__* r_textureMode ; 

void GL_SetDefaultState( void )
{
	qglClearDepth( 1.0f );

	qglCullFace(GL_FRONT);

	GL_BindNullTextures();

	if (glRefConfig.framebufferObject)
		GL_BindNullFramebuffers();

	GL_TextureMode( r_textureMode->string );

	//qglShadeModel( GL_SMOOTH );
	qglDepthFunc( GL_LEQUAL );

	//
	// make sure our GL state vector is set correctly
	//
	glState.glStateBits = GLS_DEPTHTEST_DISABLE | GLS_DEPTHMASK_TRUE;
	glState.storedGlState = 0;
	glState.faceCulling = CT_TWO_SIDED;
	glState.faceCullFront = GL_FRONT;

	GL_BindNullProgram();

	if (glRefConfig.vertexArrayObject)
		qglBindVertexArray(0);

	qglBindBuffer(GL_ARRAY_BUFFER, 0);
	qglBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glState.currentVao = NULL;
	glState.vertexAttribsEnabled = 0;

	qglPolygonMode (GL_FRONT_AND_BACK, GL_FILL);
	qglDepthMask( GL_TRUE );
	qglDisable( GL_DEPTH_TEST );
	qglEnable( GL_SCISSOR_TEST );
	qglDisable( GL_CULL_FACE );
	qglDisable( GL_BLEND );

	if (glRefConfig.seamlessCubeMap)
		qglEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);

	// GL_POLYGON_OFFSET_FILL will be glEnable()d when this is used
	qglPolygonOffset( r_offsetFactor->value, r_offsetUnits->value );

	qglClearColor( 0.0f, 0.0f, 0.0f, 1.0f );	// FIXME: get color of sky
}