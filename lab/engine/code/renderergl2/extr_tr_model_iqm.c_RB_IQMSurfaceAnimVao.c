#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  surfaceType_t ;
struct TYPE_12__ {TYPE_4__* iqmData; int /*<<< orphan*/  numVerts; int /*<<< orphan*/  numIndexes; int /*<<< orphan*/  vao; scalar_t__ iqmSurface; } ;
typedef  TYPE_3__ srfVaoIQModel_t ;
struct TYPE_13__ {int num_poses; int num_frames; } ;
typedef  TYPE_4__ iqmData_t ;
struct TYPE_16__ {TYPE_2__* currentEntity; } ;
struct TYPE_15__ {int boneAnimation; float** boneMatrix; } ;
struct TYPE_14__ {int /*<<< orphan*/  numVertexes; int /*<<< orphan*/  numIndexes; int /*<<< orphan*/  useInternalVao; int /*<<< orphan*/  cubemapIndex; int /*<<< orphan*/  fogNum; int /*<<< orphan*/  shader; } ;
struct TYPE_10__ {int frame; int oldframe; float backlerp; } ;
struct TYPE_11__ {TYPE_1__ e; } ;

/* Variables and functions */
 int /*<<< orphan*/  ComputePoseMats (TYPE_4__*,int,int,float,float*) ; 
 int IQM_MAX_JOINTS ; 
 int /*<<< orphan*/  RB_BeginSurface (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RB_EndSurface () ; 
 int /*<<< orphan*/  RB_IQMSurfaceAnim (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  R_BindVao (int /*<<< orphan*/ ) ; 
 scalar_t__ ShaderRequiresCPUDeforms (int /*<<< orphan*/ ) ; 
 TYPE_7__ backEnd ; 
 TYPE_6__ glState ; 
 int /*<<< orphan*/  qfalse ; 
 TYPE_5__ tess ; 

void RB_IQMSurfaceAnimVao(srfVaoIQModel_t * surface)
{
	iqmData_t *data = surface->iqmData;

	if (ShaderRequiresCPUDeforms(tess.shader))
	{
		RB_IQMSurfaceAnim((surfaceType_t*)surface->iqmSurface);
		return;
	}

	if(!surface->vao)
		return;

	//RB_CheckVao(surface->vao);
	RB_EndSurface();
	RB_BeginSurface(tess.shader, tess.fogNum, tess.cubemapIndex);

	R_BindVao(surface->vao);

	tess.useInternalVao = qfalse;

	tess.numIndexes = surface->numIndexes;
	tess.numVertexes = surface->numVerts;

	glState.boneAnimation = data->num_poses;

	if ( glState.boneAnimation ) {
		float		jointMats[IQM_MAX_JOINTS * 12];
		int			frame = data->num_frames ? backEnd.currentEntity->e.frame % data->num_frames : 0;
		int			oldframe = data->num_frames ? backEnd.currentEntity->e.oldframe % data->num_frames : 0;
		float		backlerp = backEnd.currentEntity->e.backlerp;
		int i;

		// compute interpolated joint matrices
		ComputePoseMats( surface->iqmData, frame, oldframe, backlerp, jointMats );

		// convert row-major order 3x4 matrix to column-major order 4x4 matrix
		for ( i = 0; i < data->num_poses; i++ ) {
			glState.boneMatrix[i][0] = jointMats[i*12+0];
			glState.boneMatrix[i][1] = jointMats[i*12+4];
			glState.boneMatrix[i][2] = jointMats[i*12+8];
			glState.boneMatrix[i][3] = 0.0f;
			glState.boneMatrix[i][4] = jointMats[i*12+1];
			glState.boneMatrix[i][5] = jointMats[i*12+5];
			glState.boneMatrix[i][6] = jointMats[i*12+9];
			glState.boneMatrix[i][7] = 0.0f;
			glState.boneMatrix[i][8] = jointMats[i*12+2];
			glState.boneMatrix[i][9] = jointMats[i*12+6];
			glState.boneMatrix[i][10] = jointMats[i*12+10];
			glState.boneMatrix[i][11] = 0.0f;
			glState.boneMatrix[i][12] = jointMats[i*12+3];
			glState.boneMatrix[i][13] = jointMats[i*12+7];
			glState.boneMatrix[i][14] = jointMats[i*12+11];
			glState.boneMatrix[i][15] = 1.0f;
		}
	}

	RB_EndSurface();

	glState.boneAnimation = 0;
}