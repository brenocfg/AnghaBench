#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_9__ ;
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  double* vec3_t ;
struct TYPE_12__ {size_t planenum; TYPE_9__* winding; TYPE_8__* shaderInfo; } ;
typedef  TYPE_1__ side_t ;
struct TYPE_13__ {int /*<<< orphan*/  shader; } ;
typedef  TYPE_2__ bspShader_t ;
typedef  int /*<<< orphan*/  bspPlane_t ;
struct TYPE_14__ {int numSides; int firstSide; } ;
typedef  TYPE_3__ bspBrush_t ;
struct TYPE_15__ {size_t shaderNum; size_t planeNum; } ;
typedef  TYPE_4__ bspBrushSide_t ;
struct TYPE_18__ {int /*<<< orphan*/ * p; } ;
struct TYPE_17__ {char* shader; } ;
struct TYPE_16__ {int numsides; TYPE_1__* sides; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  CreateBrushWindings (TYPE_5__*) ; 
 int /*<<< orphan*/  FreeWinding (TYPE_9__*) ; 
 int /*<<< orphan*/  Q_stricmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  Q_strncasecmp (char*,char*,int) ; 
 TYPE_8__* ShaderInfoForShader (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VectorAdd (int /*<<< orphan*/ ,double*,double*) ; 
 TYPE_4__* bspBrushSides ; 
 int /*<<< orphan*/ * bspPlanes ; 
 TYPE_2__* bspShaders ; 
 TYPE_5__* buildBrush ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 size_t numBSPShaders ; 

__attribute__((used)) static void ConvertBrush( FILE *f, int num, bspBrush_t *brush, vec3_t origin ){
	int i, j;
	bspBrushSide_t  *side;
	side_t          *buildSide;
	bspShader_t     *shader;
	char            *texture;
	bspPlane_t      *plane;
	vec3_t pts[ 3 ];


	/* start brush */
	fprintf( f, "\t// brush %d\n", num );
	fprintf( f, "\t{\n" );

	/* clear out build brush */
	for ( i = 0; i < buildBrush->numsides; i++ )
	{
		buildSide = &buildBrush->sides[ i ];
		if ( buildSide->winding != NULL ) {
			FreeWinding( buildSide->winding );
			buildSide->winding = NULL;
		}
	}
	buildBrush->numsides = 0;

	/* iterate through bsp brush sides */
	for ( i = 0; i < brush->numSides; i++ )
	{
		/* get side */
		side = &bspBrushSides[ brush->firstSide + i ];

		/* get shader */
		if ( side->shaderNum < 0 || side->shaderNum >= numBSPShaders ) {
			continue;
		}
		shader = &bspShaders[ side->shaderNum ];
		if ( !Q_stricmp( shader->shader, "default" ) || !Q_stricmp( shader->shader, "noshader" ) ) {
			continue;
		}

		/* get plane */
		plane = &bspPlanes[ side->planeNum ];

		/* add build side */
		buildSide = &buildBrush->sides[ buildBrush->numsides ];
		buildBrush->numsides++;

		/* tag it */
		buildSide->shaderInfo = ShaderInfoForShader( shader->shader );
		buildSide->planenum = side->planeNum;
		buildSide->winding = NULL;
	}

	/* make brush windings */
	if ( !CreateBrushWindings( buildBrush ) ) {
		return;
	}

	/* iterate through build brush sides */
	for ( i = 0; i < buildBrush->numsides; i++ )
	{
		/* get build side */
		buildSide = &buildBrush->sides[ i ];

		/* dummy check */
		if ( buildSide->shaderInfo == NULL || buildSide->winding == NULL ) {
			continue;
		}

		/* get texture name */
		if ( !Q_strncasecmp( buildSide->shaderInfo->shader, "textures/", 9 ) ) {
			texture = buildSide->shaderInfo->shader + 9;
		}
		else{
			texture = buildSide->shaderInfo->shader;
		}

		/* get plane points and offset by origin */
		for ( j = 0; j < 3; j++ )
		{
			VectorAdd( buildSide->winding->p[ j ], origin, pts[ j ] );
			//%	pts[ j ][ 0 ] = SNAP_INT_TO_FLOAT * floor( pts[ j ][ 0 ] * SNAP_FLOAT_TO_INT + 0.5f );
			//%	pts[ j ][ 1 ] = SNAP_INT_TO_FLOAT * floor( pts[ j ][ 1 ] * SNAP_FLOAT_TO_INT + 0.5f );
			//%	pts[ j ][ 2 ] = SNAP_INT_TO_FLOAT * floor( pts[ j ][ 2 ] * SNAP_FLOAT_TO_INT + 0.5f );
		}

		/* print brush side */
		/* ( 640 24 -224 ) ( 448 24 -224 ) ( 448 -232 -224 ) common/caulk 0 48 0 0.500000 0.500000 0 0 0 */
		fprintf( f, "\t\t( %.3f %.3f %.3f ) ( %.3f %.3f %.3f ) ( %.3f %.3f %.3f ) %s 0 0 0 0.5 0.5 0 0 0\n",
				 pts[ 0 ][ 0 ], pts[ 0 ][ 1 ], pts[ 0 ][ 2 ],
				 pts[ 1 ][ 0 ], pts[ 1 ][ 1 ], pts[ 1 ][ 2 ],
				 pts[ 2 ][ 0 ], pts[ 2 ][ 1 ], pts[ 2 ][ 2 ],
				 texture );
	}

	/* end brush */
	fprintf( f, "\t}\n\n" );
}