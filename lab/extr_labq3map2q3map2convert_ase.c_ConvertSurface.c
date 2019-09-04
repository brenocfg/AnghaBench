#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  double* vec3_t ;
typedef  int /*<<< orphan*/  bspModel_t ;
struct TYPE_5__ {double* xyz; double* normal; double* st; } ;
typedef  TYPE_1__ bspDrawVert_t ;
struct TYPE_6__ {int surfaceType; int shaderNum; int numVerts; int numIndexes; int firstVert; int firstIndex; } ;
typedef  TYPE_2__ bspDrawSurface_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
#define  MST_PLANAR 129 
#define  MST_TRIANGLE_SOUP 128 
 int /*<<< orphan*/  VectorAdd (double*,double*,double*) ; 
 int /*<<< orphan*/  VectorCopy (double*,double*) ; 
 scalar_t__ VectorNormalize (double*,double*) ; 
 int* bspDrawIndexes ; 
 TYPE_1__* bspDrawVerts ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int,int,int) ; 

__attribute__((used)) static void ConvertSurface( FILE *f, bspModel_t *model, int modelNum, bspDrawSurface_t *ds, int surfaceNum, vec3_t origin ){
	int i, v, face, a, b, c;
	bspDrawVert_t   *dv;
	vec3_t normal;
	char name[ 1024 ];


	/* ignore patches for now */
	if ( ds->surfaceType != MST_PLANAR && ds->surfaceType != MST_TRIANGLE_SOUP ) {
		return;
	}

	/* print object header for each dsurf */
	sprintf( name, "mat%dmodel%dsurf%d", ds->shaderNum, modelNum, surfaceNum );
	fprintf( f, "*GEOMOBJECT\t{\r\n" );
	fprintf( f, "\t*NODE_NAME\t\"%s\"\r\n", name );
	fprintf( f, "\t*NODE_TM\t{\r\n" );
	fprintf( f, "\t\t*NODE_NAME\t\"%s\"\r\n", name );
	fprintf( f, "\t\t*INHERIT_POS\t0\t0\t0\r\n" );
	fprintf( f, "\t\t*INHERIT_ROT\t0\t0\t0\r\n" );
	fprintf( f, "\t\t*INHERIT_SCL\t0\t0\t0\r\n" );
	fprintf( f, "\t\t*TM_ROW0\t1.0\t0\t0\r\n" );
	fprintf( f, "\t\t*TM_ROW1\t0\t1.0\t0\r\n" );
	fprintf( f, "\t\t*TM_ROW2\t0\t0\t1.0\r\n" );
	fprintf( f, "\t\t*TM_ROW3\t0\t0\t0\r\n" );
	fprintf( f, "\t\t*TM_POS\t%f\t%f\t%f\r\n", origin[ 0 ], origin[ 1 ], origin[ 2 ] );
	fprintf( f, "\t}\r\n" );

	/* print mesh header */
	fprintf( f, "\t*MESH\t{\r\n" );
	fprintf( f, "\t\t*TIMEVALUE\t0\r\n" );
	fprintf( f, "\t\t*MESH_NUMVERTEX\t%d\r\n", ds->numVerts );
	fprintf( f, "\t\t*MESH_NUMFACES\t%d\r\n", ds->numIndexes / 3 );
	switch ( ds->surfaceType )
	{
	case MST_PLANAR:
		fprintf( f, "\t\t*COMMENT\t\"SURFACETYPE\tMST_PLANAR\"\r\n" );
		break;
	case MST_TRIANGLE_SOUP:
		fprintf( f, "\t\t*COMMENT\t\"SURFACETYPE\tMST_TRIANGLE_SOUP\"\r\n" );
		break;
	}

	/* export vertex xyz */
	fprintf( f, "\t\t*MESH_VERTEX_LIST\t{\r\n" );
	for ( i = 0; i < ds->numVerts; i++ )
	{
		v = i + ds->firstVert;
		dv = &bspDrawVerts[ v ];
		fprintf( f, "\t\t\t*MESH_VERTEX\t%d\t%f\t%f\t%f\r\n", i, dv->xyz[ 0 ], dv->xyz[ 1 ], dv->xyz[ 2 ] );
	}
	fprintf( f, "\t\t}\r\n" );

	/* export vertex normals */
	fprintf( f, "\t\t*MESH_NORMALS\t{\r\n" );
	for ( i = 0; i < ds->numIndexes; i += 3 )
	{
		face = ( i / 3 );
		a = bspDrawIndexes[ i + ds->firstIndex ];
		b = bspDrawIndexes[ i + ds->firstIndex + 1 ];
		c = bspDrawIndexes[ i + ds->firstIndex + 2 ];
		VectorCopy( bspDrawVerts[ a ].normal, normal );
		VectorAdd( normal, bspDrawVerts[ b ].normal, normal );
		VectorAdd( normal, bspDrawVerts[ c ].normal, normal );
		if ( VectorNormalize( normal, normal ) ) {
			fprintf( f, "\t\t\t*MESH_FACENORMAL\t%d\t%f\t%f\t%f\r\n", face, normal[ 0 ], normal[ 1 ], normal[ 2 ] );
		}
	}
	for ( i = 0; i < ds->numVerts; i++ )
	{
		v = i + ds->firstVert;
		dv = &bspDrawVerts[ v ];
		fprintf( f, "\t\t\t*MESH_VERTEXNORMAL\t%d\t%f\t%f\t%f\r\n", i, dv->normal[ 0 ], dv->normal[ 1 ], dv->normal[ 2 ] );
	}
	fprintf( f, "\t\t}\r\n" );

	/* export faces */
	fprintf( f, "\t\t*MESH_FACE_LIST\t{\r\n" );
	for ( i = 0; i < ds->numIndexes; i += 3 )
	{
		face = ( i / 3 );
		a = bspDrawIndexes[ i + ds->firstIndex ];
		c = bspDrawIndexes[ i + ds->firstIndex + 1 ];
		b = bspDrawIndexes[ i + ds->firstIndex + 2 ];
		fprintf( f, "\t\t\t*MESH_FACE\t%d\tA:\t%d\tB:\t%d\tC:\t%d\tAB:\t1\tBC:\t1\tCA:\t1\t*MESH_SMOOTHING\t0\t*MESH_MTLID\t0\r\n",
				 face, a, b, c );
	}
	fprintf( f, "\t\t}\r\n" );

	/* export vertex st */
	fprintf( f, "\t\t*MESH_NUMTVERTEX\t%d\r\n", ds->numVerts );
	fprintf( f, "\t\t*MESH_TVERTLIST\t{\r\n" );
	for ( i = 0; i < ds->numVerts; i++ )
	{
		v = i + ds->firstVert;
		dv = &bspDrawVerts[ v ];
		fprintf( f, "\t\t\t*MESH_TVERT\t%d\t%f\t%f\t%f\r\n", i, dv->st[ 0 ], ( 1.0 - dv->st[ 1 ] ), 1.0f );
	}
	fprintf( f, "\t\t}\r\n" );

	/* export texture faces */
	fprintf( f, "\t\t*MESH_NUMTVFACES\t%d\r\n", ds->numIndexes / 3 );
	fprintf( f, "\t\t*MESH_TFACELIST\t{\r\n" );
	for ( i = 0; i < ds->numIndexes; i += 3 )
	{
		face = ( i / 3 );
		a = bspDrawIndexes[ i + ds->firstIndex ];
		c = bspDrawIndexes[ i + ds->firstIndex + 1 ];
		b = bspDrawIndexes[ i + ds->firstIndex + 2 ];
		fprintf( f, "\t\t\t*MESH_TFACE\t%d\t%d\t%d\t%d\r\n", face, a, b, c );
	}
	fprintf( f, "\t\t}\r\n" );

	/* print mesh footer */
	fprintf( f, "\t}\r\n" );

	/* print object footer */
	fprintf( f, "\t*PROP_MOTIONBLUR\t0\r\n" );
	fprintf( f, "\t*PROP_CASTSHADOW\t1\r\n" );
	fprintf( f, "\t*PROP_RECVSHADOW\t1\r\n" );
	fprintf( f, "\t*MATERIAL_REF\t%d\r\n", ds->shaderNum );
	fprintf( f, "}\r\n" );
}