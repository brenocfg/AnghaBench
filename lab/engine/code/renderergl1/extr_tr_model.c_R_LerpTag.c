#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  qhandle_t ;
struct TYPE_10__ {float** axis; float* origin; } ;
typedef  TYPE_1__ orientation_t ;
struct TYPE_11__ {scalar_t__ type; int /*<<< orphan*/ * md3; scalar_t__ modelData; } ;
typedef  TYPE_2__ model_t ;
typedef  int /*<<< orphan*/  mdrHeader_t ;
struct TYPE_12__ {float* origin; float** axis; } ;
typedef  TYPE_3__ md3Tag_t ;

/* Variables and functions */
 int /*<<< orphan*/  AxisClear (float**) ; 
 scalar_t__ MOD_IQM ; 
 scalar_t__ MOD_MDR ; 
 TYPE_3__* R_GetAnimTag (int /*<<< orphan*/ *,int,char const*,TYPE_3__*) ; 
 TYPE_2__* R_GetModelByHandle (int /*<<< orphan*/ ) ; 
 TYPE_3__* R_GetTag (int /*<<< orphan*/ ,int,char const*) ; 
 int R_IQMLerpTag (TYPE_1__*,scalar_t__,int,int,float,char const*) ; 
 int /*<<< orphan*/  VectorClear (float*) ; 
 int /*<<< orphan*/  VectorNormalize (float*) ; 
 int qfalse ; 
 int qtrue ; 

int R_LerpTag( orientation_t *tag, qhandle_t handle, int startFrame, int endFrame, 
					 float frac, const char *tagName ) {
	md3Tag_t	*start, *end;
	md3Tag_t	start_space, end_space;
	int		i;
	float		frontLerp, backLerp;
	model_t		*model;

	model = R_GetModelByHandle( handle );
	if ( !model->md3[0] )
	{
		if(model->type == MOD_MDR)
		{
			start = R_GetAnimTag((mdrHeader_t *) model->modelData, startFrame, tagName, &start_space);
			end = R_GetAnimTag((mdrHeader_t *) model->modelData, endFrame, tagName, &end_space);
		}
		else if( model->type == MOD_IQM ) {
			return R_IQMLerpTag( tag, model->modelData,
					startFrame, endFrame,
					frac, tagName );
		} else {
			start = end = NULL;
		}
	}
	else
	{
		start = R_GetTag( model->md3[0], startFrame, tagName );
		end = R_GetTag( model->md3[0], endFrame, tagName );
	}

	if ( !start || !end ) {
		AxisClear( tag->axis );
		VectorClear( tag->origin );
		return qfalse;
	}

	frontLerp = frac;
	backLerp = 1.0f - frac;

	for ( i = 0 ; i < 3 ; i++ ) {
		tag->origin[i] = start->origin[i] * backLerp +  end->origin[i] * frontLerp;
		tag->axis[0][i] = start->axis[0][i] * backLerp +  end->axis[0][i] * frontLerp;
		tag->axis[1][i] = start->axis[1][i] * backLerp +  end->axis[1][i] * frontLerp;
		tag->axis[2][i] = start->axis[2][i] * backLerp +  end->axis[2][i] * frontLerp;
	}
	VectorNormalize( tag->axis[0] );
	VectorNormalize( tag->axis[1] );
	VectorNormalize( tag->axis[2] );
	return qtrue;
}