#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_9__ ;
typedef  struct TYPE_18__   TYPE_8__ ;
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int numTexMods; TYPE_9__* texMods; } ;
typedef  TYPE_4__ textureBundle_t ;
struct TYPE_15__ {TYPE_4__* bundle; } ;
typedef  TYPE_5__ shaderStage_t ;
struct TYPE_19__ {int type; int /*<<< orphan*/  rotateSpeed; int /*<<< orphan*/  wave; int /*<<< orphan*/  scale; int /*<<< orphan*/  scroll; } ;
struct TYPE_18__ {TYPE_2__* currentEntity; } ;
struct TYPE_17__ {int /*<<< orphan*/  (* Error ) (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ;} ;
struct TYPE_16__ {TYPE_3__* shader; } ;
struct TYPE_13__ {int /*<<< orphan*/  name; } ;
struct TYPE_11__ {int /*<<< orphan*/  shaderTexCoord; } ;
struct TYPE_12__ {TYPE_1__ e; } ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_DROP ; 
 int /*<<< orphan*/  RB_CalcRotateTexMatrix (int /*<<< orphan*/ ,float*) ; 
 int /*<<< orphan*/  RB_CalcScaleTexMatrix (int /*<<< orphan*/ ,float*) ; 
 int /*<<< orphan*/  RB_CalcScrollTexMatrix (int /*<<< orphan*/ ,float*) ; 
 int /*<<< orphan*/  RB_CalcStretchTexMatrix (int /*<<< orphan*/ *,float*) ; 
 int /*<<< orphan*/  RB_CalcTransformTexMatrix (TYPE_9__*,float*) ; 
 int /*<<< orphan*/  RB_CalcTurbulentFactors (int /*<<< orphan*/ *,float*,float*) ; 
#define  TMOD_ENTITY_TRANSLATE 135 
#define  TMOD_NONE 134 
#define  TMOD_ROTATE 133 
#define  TMOD_SCALE 132 
#define  TMOD_SCROLL 131 
#define  TMOD_STRETCH 130 
#define  TMOD_TRANSFORM 129 
#define  TMOD_TURBULENT 128 
 int TR_MAX_TEXMODS ; 
 TYPE_8__ backEnd ; 
 TYPE_7__ ri ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 
 TYPE_6__ tess ; 

__attribute__((used)) static void ComputeTexMods( shaderStage_t *pStage, int bundleNum, float *outMatrix, float *outOffTurb)
{
	int tm;
	float matrix[6], currentmatrix[6];
	textureBundle_t *bundle = &pStage->bundle[bundleNum];

	matrix[0] = 1.0f; matrix[2] = 0.0f; matrix[4] = 0.0f;
	matrix[1] = 0.0f; matrix[3] = 1.0f; matrix[5] = 0.0f;

	currentmatrix[0] = 1.0f; currentmatrix[2] = 0.0f; currentmatrix[4] = 0.0f;
	currentmatrix[1] = 0.0f; currentmatrix[3] = 1.0f; currentmatrix[5] = 0.0f;

	outMatrix[0] = 1.0f; outMatrix[2] = 0.0f;
	outMatrix[1] = 0.0f; outMatrix[3] = 1.0f;

	outOffTurb[0] = 0.0f; outOffTurb[1] = 0.0f; outOffTurb[2] = 0.0f; outOffTurb[3] = 0.0f;

	for ( tm = 0; tm < bundle->numTexMods ; tm++ ) {
		switch ( bundle->texMods[tm].type )
		{
			
		case TMOD_NONE:
			tm = TR_MAX_TEXMODS;		// break out of for loop
			break;

		case TMOD_TURBULENT:
			RB_CalcTurbulentFactors(&bundle->texMods[tm].wave, &outOffTurb[2], &outOffTurb[3]);
			break;

		case TMOD_ENTITY_TRANSLATE:
			RB_CalcScrollTexMatrix( backEnd.currentEntity->e.shaderTexCoord, matrix );
			break;

		case TMOD_SCROLL:
			RB_CalcScrollTexMatrix( bundle->texMods[tm].scroll,
									 matrix );
			break;

		case TMOD_SCALE:
			RB_CalcScaleTexMatrix( bundle->texMods[tm].scale,
								  matrix );
			break;
		
		case TMOD_STRETCH:
			RB_CalcStretchTexMatrix( &bundle->texMods[tm].wave, 
								   matrix );
			break;

		case TMOD_TRANSFORM:
			RB_CalcTransformTexMatrix( &bundle->texMods[tm],
									 matrix );
			break;

		case TMOD_ROTATE:
			RB_CalcRotateTexMatrix( bundle->texMods[tm].rotateSpeed,
									matrix );
			break;

		default:
			ri.Error( ERR_DROP, "ERROR: unknown texmod '%d' in shader '%s'", bundle->texMods[tm].type, tess.shader->name );
			break;
		}

		switch ( bundle->texMods[tm].type )
		{	
		case TMOD_NONE:
		case TMOD_TURBULENT:
		default:
			break;

		case TMOD_ENTITY_TRANSLATE:
		case TMOD_SCROLL:
		case TMOD_SCALE:
		case TMOD_STRETCH:
		case TMOD_TRANSFORM:
		case TMOD_ROTATE:
			outMatrix[0] = matrix[0] * currentmatrix[0] + matrix[2] * currentmatrix[1];
			outMatrix[1] = matrix[1] * currentmatrix[0] + matrix[3] * currentmatrix[1];

			outMatrix[2] = matrix[0] * currentmatrix[2] + matrix[2] * currentmatrix[3];
			outMatrix[3] = matrix[1] * currentmatrix[2] + matrix[3] * currentmatrix[3];

			outOffTurb[0] = matrix[0] * currentmatrix[4] + matrix[2] * currentmatrix[5] + matrix[4];
			outOffTurb[1] = matrix[1] * currentmatrix[4] + matrix[3] * currentmatrix[5] + matrix[5];

			currentmatrix[0] = outMatrix[0];
			currentmatrix[1] = outMatrix[1];
			currentmatrix[2] = outMatrix[2];
			currentmatrix[3] = outMatrix[3];
			currentmatrix[4] = outOffTurb[0];
			currentmatrix[5] = outOffTurb[1];
			break;
		}
	}
}