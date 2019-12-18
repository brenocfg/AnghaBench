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
typedef  int /*<<< orphan*/  vec3_t ;
struct TYPE_10__ {TYPE_1__* currentEntity; } ;
struct TYPE_9__ {int stencilBits; } ;
struct TYPE_8__ {int numVertexes; float** xyz; int numIndexes; int* indexes; } ;
struct TYPE_7__ {int /*<<< orphan*/  whiteImage; } ;
struct TYPE_6__ {int /*<<< orphan*/  modelLightDir; } ;
typedef  int /*<<< orphan*/  GLboolean ;

/* Variables and functions */
 int /*<<< orphan*/  CT_BACK_SIDED ; 
 int /*<<< orphan*/  CT_FRONT_SIDED ; 
 int /*<<< orphan*/  Com_Memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  CrossProduct (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 float DotProduct (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int GLS_DSTBLEND_ZERO ; 
 int GLS_SRCBLEND_ONE ; 
 int /*<<< orphan*/  GL_ALWAYS ; 
 int /*<<< orphan*/  GL_BindToTMU (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GL_COLOR_WRITEMASK ; 
 int /*<<< orphan*/  GL_Cull (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GL_DECR ; 
 int /*<<< orphan*/  GL_FALSE ; 
 int /*<<< orphan*/  GL_INCR ; 
 int /*<<< orphan*/  GL_KEEP ; 
 int /*<<< orphan*/  GL_STENCIL_TEST ; 
 int /*<<< orphan*/  GL_State (int) ; 
 int /*<<< orphan*/  R_AddEdgeDef (int,int,int) ; 
 int /*<<< orphan*/  R_RenderShadowEdges () ; 
 int /*<<< orphan*/  TB_COLORMAP ; 
 int /*<<< orphan*/  VectorCopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VectorMA (float*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VectorSubtract (float*,float*,int /*<<< orphan*/ ) ; 
 TYPE_5__ backEnd ; 
 int* facing ; 
 TYPE_4__ glConfig ; 
 int /*<<< orphan*/  numEdgeDefs ; 
 int /*<<< orphan*/  qglColor3f (float,float,float) ; 
 int /*<<< orphan*/  qglColorMask (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qglEnable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qglGetBooleanv (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qglStencilFunc (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  qglStencilOp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * shadowXyz ; 
 TYPE_3__ tess ; 
 TYPE_2__ tr ; 

void RB_ShadowTessEnd( void ) {
	// FIXME: implement this
#if 0
	int		i;
	int		numTris;
	vec3_t	lightDir;
	GLboolean rgba[4];

	if ( glConfig.stencilBits < 4 ) {
		return;
	}

	VectorCopy( backEnd.currentEntity->modelLightDir, lightDir );

	// project vertexes away from light direction
	for ( i = 0 ; i < tess.numVertexes ; i++ ) {
		VectorMA( tess.xyz[i], -512, lightDir, shadowXyz[i] );
	}

	// decide which triangles face the light
	Com_Memset( numEdgeDefs, 0, 4 * tess.numVertexes );

	numTris = tess.numIndexes / 3;
	for ( i = 0 ; i < numTris ; i++ ) {
		int		i1, i2, i3;
		vec3_t	d1, d2, normal;
		float	*v1, *v2, *v3;
		float	d;

		i1 = tess.indexes[ i*3 + 0 ];
		i2 = tess.indexes[ i*3 + 1 ];
		i3 = tess.indexes[ i*3 + 2 ];

		v1 = tess.xyz[ i1 ];
		v2 = tess.xyz[ i2 ];
		v3 = tess.xyz[ i3 ];

		VectorSubtract( v2, v1, d1 );
		VectorSubtract( v3, v1, d2 );
		CrossProduct( d1, d2, normal );

		d = DotProduct( normal, lightDir );
		if ( d > 0 ) {
			facing[ i ] = 1;
		} else {
			facing[ i ] = 0;
		}

		// create the edges
		R_AddEdgeDef( i1, i2, facing[ i ] );
		R_AddEdgeDef( i2, i3, facing[ i ] );
		R_AddEdgeDef( i3, i1, facing[ i ] );
	}

	// draw the silhouette edges

	GL_BindToTMU( tr.whiteImage, TB_COLORMAP );
	GL_State( GLS_SRCBLEND_ONE | GLS_DSTBLEND_ZERO );
	qglColor3f( 0.2f, 0.2f, 0.2f );

	// don't write to the color buffer
	qglGetBooleanv(GL_COLOR_WRITEMASK, rgba);
	qglColorMask( GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE );

	qglEnable( GL_STENCIL_TEST );
	qglStencilFunc( GL_ALWAYS, 1, 255 );

	GL_Cull( CT_BACK_SIDED );
	qglStencilOp( GL_KEEP, GL_KEEP, GL_INCR );

	R_RenderShadowEdges();

	GL_Cull( CT_FRONT_SIDED );
	qglStencilOp( GL_KEEP, GL_KEEP, GL_DECR );

	R_RenderShadowEdges();


	// reenable writing to the color buffer
	qglColorMask(rgba[0], rgba[1], rgba[2], rgba[3]);
#endif
}