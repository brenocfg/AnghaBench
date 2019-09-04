#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  float* vec4_t ;
typedef  float* vec2_t ;
typedef  int /*<<< orphan*/  surfaceType_t ;
struct TYPE_12__ {int num_vertexes; int num_triangles; int first_vertex; int num_influences; int first_influence; int first_triangle; TYPE_5__* data; } ;
typedef  TYPE_4__ srfIQModel_t ;
typedef  int /*<<< orphan*/  outColor ;
struct TYPE_11__ {float* f; scalar_t__* b; } ;
struct TYPE_13__ {int num_frames; float* positions; float* normals; float* texcoords; scalar_t__ num_poses; scalar_t__ blendWeightsType; int* influenceBlendIndexes; int* influences; int* triangles; TYPE_3__ influenceBlendWeights; int /*<<< orphan*/ * colors; } ;
typedef  TYPE_5__ iqmData_t ;
typedef  size_t glIndex_t ;
typedef  int /*<<< orphan*/  color4ub_t ;
typedef  int /*<<< orphan*/  byte ;
struct TYPE_15__ {TYPE_2__* currentEntity; } ;
struct TYPE_14__ {float** xyz; size_t numVertexes; float** normal; float*** texCoords; size_t* indexes; size_t numIndexes; int /*<<< orphan*/ * vertexColors; } ;
struct TYPE_9__ {int frame; int oldframe; float backlerp; } ;
struct TYPE_10__ {TYPE_1__ e; } ;

/* Variables and functions */
 int /*<<< orphan*/  Com_Memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  Com_Memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ComputePoseMats (TYPE_5__*,int,int,float,float*) ; 
 scalar_t__ IQM_FLOAT ; 
 int IQM_MAX_JOINTS ; 
 int /*<<< orphan*/  RB_CHECKOVERFLOW (int,int) ; 
 int SHADER_MAX_VERTEXES ; 
 TYPE_7__ backEnd ; 
 float* identityMatrix ; 
 TYPE_6__ tess ; 

void RB_IQMSurfaceAnim( surfaceType_t *surface ) {
	srfIQModel_t	*surf = (srfIQModel_t *)surface;
	iqmData_t	*data = surf->data;
	float		poseMats[IQM_MAX_JOINTS * 12];
	float		influenceVtxMat[SHADER_MAX_VERTEXES * 12];
	float		influenceNrmMat[SHADER_MAX_VERTEXES * 9];
	int		i;

	float		*xyz;
	float		*normal;
	float		*texCoords;
	byte		*color;
	vec4_t		*outXYZ;
	vec4_t		*outNormal;
	vec2_t		(*outTexCoord)[2];
	color4ub_t	*outColor;

	int	frame = data->num_frames ? backEnd.currentEntity->e.frame % data->num_frames : 0;
	int	oldframe = data->num_frames ? backEnd.currentEntity->e.oldframe % data->num_frames : 0;
	float	backlerp = backEnd.currentEntity->e.backlerp;

	int		*tri;
	glIndex_t	*ptr;
	glIndex_t	base;

	RB_CHECKOVERFLOW( surf->num_vertexes, surf->num_triangles * 3 );

	xyz = &data->positions[surf->first_vertex * 3];
	normal = &data->normals[surf->first_vertex * 3];
	texCoords = &data->texcoords[surf->first_vertex * 2];

	if ( data->colors ) {
		color = &data->colors[surf->first_vertex * 4];
	} else {
		color = NULL;
	}

	outXYZ = &tess.xyz[tess.numVertexes];
	outNormal = &tess.normal[tess.numVertexes];
	outTexCoord = &tess.texCoords[tess.numVertexes];
	outColor = &tess.vertexColors[tess.numVertexes];

	if ( data->num_poses > 0 ) {
		// compute interpolated joint matrices
		ComputePoseMats( data, frame, oldframe, backlerp, poseMats );

		// compute vertex blend influence matricies
		for( i = 0; i < surf->num_influences; i++ ) {
			int influence = surf->first_influence + i;
			float *vtxMat = &influenceVtxMat[12*i];
			float *nrmMat = &influenceNrmMat[9*i];
			int	j;
			float	blendWeights[4];
			int		numWeights;

			for ( numWeights = 0; numWeights < 4; numWeights++ ) {
				if ( data->blendWeightsType == IQM_FLOAT )
					blendWeights[numWeights] = data->influenceBlendWeights.f[4*influence + numWeights];
				else
					blendWeights[numWeights] = (float)data->influenceBlendWeights.b[4*influence + numWeights] / 255.0f;

				if ( blendWeights[numWeights] <= 0.0f )
					break;
			}

			if ( numWeights == 0 ) {
				// no blend joint, use identity matrix.
				vtxMat[0] = identityMatrix[0];
				vtxMat[1] = identityMatrix[1];
				vtxMat[2] = identityMatrix[2];
				vtxMat[3] = identityMatrix[3];
				vtxMat[4] = identityMatrix[4];
				vtxMat[5] = identityMatrix[5];
				vtxMat[6] = identityMatrix[6];
				vtxMat[7] = identityMatrix[7];
				vtxMat[8] = identityMatrix[8];
				vtxMat[9] = identityMatrix[9];
				vtxMat[10] = identityMatrix[10];
				vtxMat[11] = identityMatrix[11];
			} else {
				// compute the vertex matrix by blending the up to
				// four blend weights
				vtxMat[0] = blendWeights[0] * poseMats[12 * data->influenceBlendIndexes[4*influence + 0] + 0];
				vtxMat[1] = blendWeights[0] * poseMats[12 * data->influenceBlendIndexes[4*influence + 0] + 1];
				vtxMat[2] = blendWeights[0] * poseMats[12 * data->influenceBlendIndexes[4*influence + 0] + 2];
				vtxMat[3] = blendWeights[0] * poseMats[12 * data->influenceBlendIndexes[4*influence + 0] + 3];
				vtxMat[4] = blendWeights[0] * poseMats[12 * data->influenceBlendIndexes[4*influence + 0] + 4];
				vtxMat[5] = blendWeights[0] * poseMats[12 * data->influenceBlendIndexes[4*influence + 0] + 5];
				vtxMat[6] = blendWeights[0] * poseMats[12 * data->influenceBlendIndexes[4*influence + 0] + 6];
				vtxMat[7] = blendWeights[0] * poseMats[12 * data->influenceBlendIndexes[4*influence + 0] + 7];
				vtxMat[8] = blendWeights[0] * poseMats[12 * data->influenceBlendIndexes[4*influence + 0] + 8];
				vtxMat[9] = blendWeights[0] * poseMats[12 * data->influenceBlendIndexes[4*influence + 0] + 9];
				vtxMat[10] = blendWeights[0] * poseMats[12 * data->influenceBlendIndexes[4*influence + 0] + 10];
				vtxMat[11] = blendWeights[0] * poseMats[12 * data->influenceBlendIndexes[4*influence + 0] + 11];

				for( j = 1; j < numWeights; j++ ) {
					vtxMat[0] += blendWeights[j] * poseMats[12 * data->influenceBlendIndexes[4*influence + j] + 0];
					vtxMat[1] += blendWeights[j] * poseMats[12 * data->influenceBlendIndexes[4*influence + j] + 1];
					vtxMat[2] += blendWeights[j] * poseMats[12 * data->influenceBlendIndexes[4*influence + j] + 2];
					vtxMat[3] += blendWeights[j] * poseMats[12 * data->influenceBlendIndexes[4*influence + j] + 3];
					vtxMat[4] += blendWeights[j] * poseMats[12 * data->influenceBlendIndexes[4*influence + j] + 4];
					vtxMat[5] += blendWeights[j] * poseMats[12 * data->influenceBlendIndexes[4*influence + j] + 5];
					vtxMat[6] += blendWeights[j] * poseMats[12 * data->influenceBlendIndexes[4*influence + j] + 6];
					vtxMat[7] += blendWeights[j] * poseMats[12 * data->influenceBlendIndexes[4*influence + j] + 7];
					vtxMat[8] += blendWeights[j] * poseMats[12 * data->influenceBlendIndexes[4*influence + j] + 8];
					vtxMat[9] += blendWeights[j] * poseMats[12 * data->influenceBlendIndexes[4*influence + j] + 9];
					vtxMat[10] += blendWeights[j] * poseMats[12 * data->influenceBlendIndexes[4*influence + j] + 10];
					vtxMat[11] += blendWeights[j] * poseMats[12 * data->influenceBlendIndexes[4*influence + j] + 11];
				}
			}

			// compute the normal matrix as transpose of the adjoint
			// of the vertex matrix
			nrmMat[ 0] = vtxMat[ 5]*vtxMat[10] - vtxMat[ 6]*vtxMat[ 9];
			nrmMat[ 1] = vtxMat[ 6]*vtxMat[ 8] - vtxMat[ 4]*vtxMat[10];
			nrmMat[ 2] = vtxMat[ 4]*vtxMat[ 9] - vtxMat[ 5]*vtxMat[ 8];
			nrmMat[ 3] = vtxMat[ 2]*vtxMat[ 9] - vtxMat[ 1]*vtxMat[10];
			nrmMat[ 4] = vtxMat[ 0]*vtxMat[10] - vtxMat[ 2]*vtxMat[ 8];
			nrmMat[ 5] = vtxMat[ 1]*vtxMat[ 8] - vtxMat[ 0]*vtxMat[ 9];
			nrmMat[ 6] = vtxMat[ 1]*vtxMat[ 6] - vtxMat[ 2]*vtxMat[ 5];
			nrmMat[ 7] = vtxMat[ 2]*vtxMat[ 4] - vtxMat[ 0]*vtxMat[ 6];
			nrmMat[ 8] = vtxMat[ 0]*vtxMat[ 5] - vtxMat[ 1]*vtxMat[ 4];
		}

		// transform vertexes and fill other data
		for( i = 0; i < surf->num_vertexes;
		     i++, xyz+=3, normal+=3, texCoords+=2,
		     outXYZ++, outNormal++, outTexCoord++ ) {
			int influence = data->influences[surf->first_vertex + i] - surf->first_influence;
			float *vtxMat = &influenceVtxMat[12*influence];
			float *nrmMat = &influenceNrmMat[9*influence];

			(*outTexCoord)[0][0] = texCoords[0];
			(*outTexCoord)[0][1] = texCoords[1];

			(*outXYZ)[0] =
				vtxMat[ 0] * xyz[0] +
				vtxMat[ 1] * xyz[1] +
				vtxMat[ 2] * xyz[2] +
				vtxMat[ 3];
			(*outXYZ)[1] =
				vtxMat[ 4] * xyz[0] +
				vtxMat[ 5] * xyz[1] +
				vtxMat[ 6] * xyz[2] +
				vtxMat[ 7];
			(*outXYZ)[2] =
				vtxMat[ 8] * xyz[0] +
				vtxMat[ 9] * xyz[1] +
				vtxMat[10] * xyz[2] +
				vtxMat[11];

			(*outNormal)[0] =
				nrmMat[ 0] * normal[0] +
				nrmMat[ 1] * normal[1] +
				nrmMat[ 2] * normal[2];
			(*outNormal)[1] =
				nrmMat[ 3] * normal[0] +
				nrmMat[ 4] * normal[1] +
				nrmMat[ 5] * normal[2];
			(*outNormal)[2] =
				nrmMat[ 6] * normal[0] +
				nrmMat[ 7] * normal[1] +
				nrmMat[ 8] * normal[2];
		}
	} else {
		// copy vertexes and fill other data
		for( i = 0; i < surf->num_vertexes;
		     i++, xyz+=3, normal+=3, texCoords+=2,
		     outXYZ++, outNormal++, outTexCoord++ ) {
			(*outTexCoord)[0][0] = texCoords[0];
			(*outTexCoord)[0][1] = texCoords[1];

			(*outXYZ)[0] = xyz[0];
			(*outXYZ)[1] = xyz[1];
			(*outXYZ)[2] = xyz[2];

			(*outNormal)[0] = normal[0];
			(*outNormal)[1] = normal[1];
			(*outNormal)[2] = normal[2];
		}
	}

	if ( color ) {
		Com_Memcpy( outColor, color, surf->num_vertexes * sizeof( outColor[0] ) );
	} else {
		Com_Memset( outColor, 0, surf->num_vertexes * sizeof( outColor[0] ) );
	}

	tri = data->triangles + 3 * surf->first_triangle;
	ptr = &tess.indexes[tess.numIndexes];
	base = tess.numVertexes;

	for( i = 0; i < surf->num_triangles; i++ ) {
		*ptr++ = base + (*tri++ - surf->first_vertex);
		*ptr++ = base + (*tri++ - surf->first_vertex);
		*ptr++ = base + (*tri++ - surf->first_vertex);
	}

	tess.numIndexes += 3 * surf->num_triangles;
	tess.numVertexes += surf->num_vertexes;
}