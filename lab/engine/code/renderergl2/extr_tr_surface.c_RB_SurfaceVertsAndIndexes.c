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
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_6__ {int /*<<< orphan*/  lightdir; int /*<<< orphan*/  color; int /*<<< orphan*/  lightmap; int /*<<< orphan*/  st; int /*<<< orphan*/  tangent; int /*<<< orphan*/  normal; int /*<<< orphan*/  xyz; } ;
typedef  TYPE_2__ srfVert_t ;
typedef  int /*<<< orphan*/  int16_t ;
typedef  int /*<<< orphan*/  glIndex_t ;
struct TYPE_7__ {size_t numIndexes; size_t numVertexes; float** xyz; float** texCoords; float** lightCoords; int* vertexDlightBits; int dlightBits; int pshadowBits; int /*<<< orphan*/ ** lightdir; TYPE_1__* shader; int /*<<< orphan*/ ** color; int /*<<< orphan*/ ** tangent; int /*<<< orphan*/ ** normal; int /*<<< orphan*/ * indexes; int /*<<< orphan*/  vao; } ;
struct TYPE_5__ {int vertexAttribs; } ;

/* Variables and functions */
 int ATTR_COLOR ; 
 int ATTR_LIGHTCOORD ; 
 int ATTR_LIGHTDIRECTION ; 
 int ATTR_NORMAL ; 
 int ATTR_POSITION ; 
 int ATTR_TANGENT ; 
 int ATTR_TEXCOORD ; 
 int /*<<< orphan*/  RB_CHECKOVERFLOW (int,int) ; 
 int /*<<< orphan*/  RB_CheckVao (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VectorCopy (int /*<<< orphan*/ ,float*) ; 
 int /*<<< orphan*/  VectorCopy2 (int /*<<< orphan*/ ,float*) ; 
 int /*<<< orphan*/  VectorCopy4 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_3__ tess ; 

__attribute__((used)) static void RB_SurfaceVertsAndIndexes( int numVerts, srfVert_t *verts, int numIndexes, glIndex_t *indexes, int dlightBits, int pshadowBits)
{
	int             i;
	glIndex_t      *inIndex;
	srfVert_t      *dv;
	float          *xyz, *texCoords, *lightCoords;
	int16_t        *lightdir;
	int16_t        *normal;
	int16_t        *tangent;
	glIndex_t      *outIndex;
	uint16_t       *color;

	RB_CheckVao(tess.vao);

	RB_CHECKOVERFLOW( numVerts, numIndexes );

	inIndex = indexes;
	outIndex = &tess.indexes[ tess.numIndexes ];
	for ( i = 0 ; i < numIndexes ; i++ ) {
		*outIndex++ = tess.numVertexes + *inIndex++;
	}
	tess.numIndexes += numIndexes;

	if ( tess.shader->vertexAttribs & ATTR_POSITION )
	{
		dv = verts;
		xyz = tess.xyz[ tess.numVertexes ];
		for ( i = 0 ; i < numVerts ; i++, dv++, xyz+=4 )
			VectorCopy(dv->xyz, xyz);
	}

	if ( tess.shader->vertexAttribs & ATTR_NORMAL )
	{
		dv = verts;
		normal = tess.normal[ tess.numVertexes ];
		for ( i = 0 ; i < numVerts ; i++, dv++, normal+=4 )
			VectorCopy4(dv->normal, normal);
	}

	if ( tess.shader->vertexAttribs & ATTR_TANGENT )
	{
		dv = verts;
		tangent = tess.tangent[ tess.numVertexes ];
		for ( i = 0 ; i < numVerts ; i++, dv++, tangent+=4 )
			VectorCopy4(dv->tangent, tangent);
	}

	if ( tess.shader->vertexAttribs & ATTR_TEXCOORD )
	{
		dv = verts;
		texCoords = tess.texCoords[tess.numVertexes];
		for ( i = 0 ; i < numVerts ; i++, dv++, texCoords+=2 )
			VectorCopy2(dv->st, texCoords);
	}

	if ( tess.shader->vertexAttribs & ATTR_LIGHTCOORD )
	{
		dv = verts;
		lightCoords = tess.lightCoords[ tess.numVertexes ];
		for ( i = 0 ; i < numVerts ; i++, dv++, lightCoords+=2 )
			VectorCopy2(dv->lightmap, lightCoords);
	}

	if ( tess.shader->vertexAttribs & ATTR_COLOR )
	{
		dv = verts;
		color = tess.color[ tess.numVertexes ];
		for ( i = 0 ; i < numVerts ; i++, dv++, color+=4 )
			VectorCopy4(dv->color, color);
	}

	if ( tess.shader->vertexAttribs & ATTR_LIGHTDIRECTION )
	{
		dv = verts;
		lightdir = tess.lightdir[ tess.numVertexes ];
		for ( i = 0 ; i < numVerts ; i++, dv++, lightdir+=4 )
			VectorCopy4(dv->lightdir, lightdir);
	}

#if 0  // nothing even uses vertex dlightbits
	for ( i = 0 ; i < numVerts ; i++ ) {
		tess.vertexDlightBits[ tess.numVertexes + i ] = dlightBits;
	}
#endif

	tess.dlightBits |= dlightBits;
	tess.pshadowBits |= pshadowBits;

	tess.numVertexes += numVerts;
}