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
typedef  int /*<<< orphan*/  vec3_t ;
typedef  int /*<<< orphan*/  qhandle_t ;
struct TYPE_10__ {scalar_t__ type; TYPE_7__* modelData; TYPE_5__** md3; TYPE_1__* bmodel; } ;
typedef  TYPE_2__ model_t ;
struct TYPE_11__ {int ofsFrames; } ;
typedef  TYPE_3__ mdrHeader_t ;
struct TYPE_12__ {scalar_t__* bounds; } ;
typedef  TYPE_4__ mdrFrame_t ;
struct TYPE_13__ {int ofsFrames; } ;
typedef  TYPE_5__ md3Header_t ;
struct TYPE_14__ {scalar_t__* bounds; } ;
typedef  TYPE_6__ md3Frame_t ;
struct TYPE_15__ {scalar_t__ bounds; } ;
typedef  TYPE_7__ iqmData_t ;
typedef  int /*<<< orphan*/  byte ;
struct TYPE_9__ {scalar_t__* bounds; } ;

/* Variables and functions */
 scalar_t__ MOD_BRUSH ; 
 scalar_t__ MOD_IQM ; 
 scalar_t__ MOD_MDR ; 
 scalar_t__ MOD_MESH ; 
 TYPE_2__* R_GetModelByHandle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VectorClear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VectorCopy (scalar_t__,int /*<<< orphan*/ ) ; 

void R_ModelBounds( qhandle_t handle, vec3_t mins, vec3_t maxs ) {
	model_t		*model;

	model = R_GetModelByHandle( handle );

	if(model->type == MOD_BRUSH) {
		VectorCopy( model->bmodel->bounds[0], mins );
		VectorCopy( model->bmodel->bounds[1], maxs );
		
		return;
	} else if (model->type == MOD_MESH) {
		md3Header_t	*header;
		md3Frame_t	*frame;

		header = model->md3[0];
		frame = (md3Frame_t *) ((byte *)header + header->ofsFrames);

		VectorCopy( frame->bounds[0], mins );
		VectorCopy( frame->bounds[1], maxs );
		
		return;
	} else if (model->type == MOD_MDR) {
		mdrHeader_t	*header;
		mdrFrame_t	*frame;

		header = (mdrHeader_t *)model->modelData;
		frame = (mdrFrame_t *) ((byte *)header + header->ofsFrames);

		VectorCopy( frame->bounds[0], mins );
		VectorCopy( frame->bounds[1], maxs );
		
		return;
	} else if(model->type == MOD_IQM) {
		iqmData_t *iqmData;
		
		iqmData = model->modelData;

		if(iqmData->bounds)
		{
			VectorCopy(iqmData->bounds, mins);
			VectorCopy(iqmData->bounds + 3, maxs);
			return;
		}
	}

	VectorClear( mins );
	VectorClear( maxs );
}