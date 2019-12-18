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
typedef  float* vec3_t ;
struct TYPE_10__ {TYPE_2__* currentEntity; } ;
struct TYPE_9__ {int integer; } ;
struct TYPE_8__ {size_t numVertexes; int** texCoords; int** color; int* indexes; int /*<<< orphan*/  numIndexes; int /*<<< orphan*/ * xyz; int /*<<< orphan*/  vao; } ;
struct TYPE_6__ {int* shaderRGBA; } ;
struct TYPE_7__ {TYPE_1__ e; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEG2RAD (int) ; 
 int /*<<< orphan*/  RB_CHECKOVERFLOW (int,int) ; 
 int /*<<< orphan*/  RB_CheckVao (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VectorAdd (float* const,float* const,float*) ; 
 int /*<<< orphan*/  VectorCopy (float*,int /*<<< orphan*/ ) ; 
 TYPE_5__ backEnd ; 
 float cos (int /*<<< orphan*/ ) ; 
 TYPE_4__* r_railWidth ; 
 float sin (int /*<<< orphan*/ ) ; 
 TYPE_3__ tess ; 

__attribute__((used)) static void DoRailDiscs( int numSegs, const vec3_t start, const vec3_t dir, const vec3_t right, const vec3_t up )
{
	int i;
	vec3_t	pos[4];
	vec3_t	v;
	int		spanWidth = r_railWidth->integer;
	float c, s;
	float		scale;

	if ( numSegs > 1 )
		numSegs--;
	if ( !numSegs )
		return;

	scale = 0.25;

	for ( i = 0; i < 4; i++ )
	{
		c = cos( DEG2RAD( 45 + i * 90 ) );
		s = sin( DEG2RAD( 45 + i * 90 ) );
		v[0] = ( right[0] * c + up[0] * s ) * scale * spanWidth;
		v[1] = ( right[1] * c + up[1] * s ) * scale * spanWidth;
		v[2] = ( right[2] * c + up[2] * s ) * scale * spanWidth;
		VectorAdd( start, v, pos[i] );

		if ( numSegs > 1 )
		{
			// offset by 1 segment if we're doing a long distance shot
			VectorAdd( pos[i], dir, pos[i] );
		}
	}

	RB_CheckVao(tess.vao);

	for ( i = 0; i < numSegs; i++ )
	{
		int j;

		RB_CHECKOVERFLOW( 4, 6 );

		for ( j = 0; j < 4; j++ )
		{
			VectorCopy( pos[j], tess.xyz[tess.numVertexes] );
			tess.texCoords[tess.numVertexes][0] = (j < 2);
			tess.texCoords[tess.numVertexes][1] = (j && j != 3);
			tess.color[tess.numVertexes][0] = backEnd.currentEntity->e.shaderRGBA[0] * 257;
			tess.color[tess.numVertexes][1] = backEnd.currentEntity->e.shaderRGBA[1] * 257;
			tess.color[tess.numVertexes][2] = backEnd.currentEntity->e.shaderRGBA[2] * 257;
			tess.numVertexes++;

			VectorAdd( pos[j], dir, pos[j] );
		}

		tess.indexes[tess.numIndexes++] = tess.numVertexes - 4 + 0;
		tess.indexes[tess.numIndexes++] = tess.numVertexes - 4 + 1;
		tess.indexes[tess.numIndexes++] = tess.numVertexes - 4 + 3;
		tess.indexes[tess.numIndexes++] = tess.numVertexes - 4 + 3;
		tess.indexes[tess.numIndexes++] = tess.numVertexes - 4 + 1;
		tess.indexes[tess.numIndexes++] = tess.numVertexes - 4 + 2;
	}
}