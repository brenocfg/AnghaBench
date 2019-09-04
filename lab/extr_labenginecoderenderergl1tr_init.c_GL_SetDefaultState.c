#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  current_color ;
struct TYPE_4__ {int glStateBits; } ;
struct TYPE_3__ {int /*<<< orphan*/  string; } ;
typedef  int GLfloat ;

/* Variables and functions */
 int GLS_DEPTHMASK_TRUE ; 
 int GLS_DEPTHTEST_DISABLE ; 
 int /*<<< orphan*/  GL_BLEND ; 
 int /*<<< orphan*/  GL_CULL_FACE ; 
 int /*<<< orphan*/  GL_CURRENT_COLOR ; 
 int /*<<< orphan*/  GL_DEPTH_TEST ; 
 int /*<<< orphan*/  GL_FILL ; 
 int /*<<< orphan*/  GL_FRONT ; 
 int /*<<< orphan*/  GL_FRONT_AND_BACK ; 
 int /*<<< orphan*/  GL_LEQUAL ; 
 int /*<<< orphan*/  GL_MODULATE ; 
 int /*<<< orphan*/  GL_SCISSOR_TEST ; 
 int /*<<< orphan*/  GL_SMOOTH ; 
 int /*<<< orphan*/  GL_SelectTexture (int) ; 
 int /*<<< orphan*/  GL_TEXTURE_2D ; 
 int /*<<< orphan*/  GL_TRUE ; 
 int /*<<< orphan*/  GL_TexEnv (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GL_TextureMode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GL_VERTEX_ARRAY ; 
 TYPE_2__ glState ; 
 scalar_t__ memcmp (int*,int const*,int) ; 
 scalar_t__ qglActiveTextureARB ; 
 int /*<<< orphan*/  qglClearDepth (float) ; 
 int /*<<< orphan*/  qglColor4f (int,int,int,int) ; 
 int /*<<< orphan*/  qglCullFace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qglDepthFunc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qglDepthMask (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qglDisable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qglEnable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qglEnableClientState (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qglGetFloatv (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  qglPolygonMode (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qglShadeModel (int /*<<< orphan*/ ) ; 
 TYPE_1__* r_textureMode ; 

void GL_SetDefaultState( void )
{
	static const GLfloat initial_color[4] = {1, 1, 1, 1};
	GLfloat current_color[4];

	qglClearDepth( 1.0f );

	qglCullFace(GL_FRONT);

	qglGetFloatv(GL_CURRENT_COLOR, current_color);

	// Because of a bug in NVIDIA's driver, we should only change glColor if it is needed.
	if (memcmp(current_color, initial_color, sizeof(current_color)) != 0) {
		qglColor4f (1,1,1,1);
	}

	// initialize downstream texture unit if we're running
	// in a multitexture environment
	if ( qglActiveTextureARB ) {
		GL_SelectTexture( 1 );
		GL_TextureMode( r_textureMode->string );
		GL_TexEnv( GL_MODULATE );
		qglDisable( GL_TEXTURE_2D );
		GL_SelectTexture( 0 );
	}

	qglEnable(GL_TEXTURE_2D);
	GL_TextureMode( r_textureMode->string );
	GL_TexEnv( GL_MODULATE );

	qglShadeModel( GL_SMOOTH );
	qglDepthFunc( GL_LEQUAL );

	// the vertex array is always enabled, but the color and texture
	// arrays are enabled and disabled around the compiled vertex array call
	qglEnableClientState (GL_VERTEX_ARRAY);

	//
	// make sure our GL state vector is set correctly
	//
	glState.glStateBits = GLS_DEPTHTEST_DISABLE | GLS_DEPTHMASK_TRUE;

	qglPolygonMode (GL_FRONT_AND_BACK, GL_FILL);
	qglDepthMask( GL_TRUE );
	qglDisable( GL_DEPTH_TEST );
	qglEnable( GL_SCISSOR_TEST );
	qglDisable( GL_CULL_FACE );
	qglDisable( GL_BLEND );
}