#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int deformation; } ;
typedef  TYPE_2__ deformStage_t ;
struct TYPE_14__ {int numDeforms; TYPE_2__* deforms; } ;
struct TYPE_10__ {int /*<<< orphan*/ * text; } ;
struct TYPE_13__ {TYPE_1__ refdef; } ;
struct TYPE_12__ {TYPE_5__* shader; } ;

/* Variables and functions */
 int /*<<< orphan*/  Autosprite2Deform () ; 
 int /*<<< orphan*/  AutospriteDeform () ; 
#define  DEFORM_AUTOSPRITE 143 
#define  DEFORM_AUTOSPRITE2 142 
#define  DEFORM_BULGE 141 
#define  DEFORM_MOVE 140 
#define  DEFORM_NONE 139 
#define  DEFORM_NORMALS 138 
#define  DEFORM_PROJECTION_SHADOW 137 
#define  DEFORM_TEXT0 136 
#define  DEFORM_TEXT1 135 
#define  DEFORM_TEXT2 134 
#define  DEFORM_TEXT3 133 
#define  DEFORM_TEXT4 132 
#define  DEFORM_TEXT5 131 
#define  DEFORM_TEXT6 130 
#define  DEFORM_TEXT7 129 
#define  DEFORM_WAVE 128 
 int /*<<< orphan*/  DeformText (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RB_CalcBulgeVertexes (TYPE_2__*) ; 
 int /*<<< orphan*/  RB_CalcDeformNormals (TYPE_2__*) ; 
 int /*<<< orphan*/  RB_CalcDeformVertexes (TYPE_2__*) ; 
 int /*<<< orphan*/  RB_CalcMoveVertexes (TYPE_2__*) ; 
 int /*<<< orphan*/  RB_ProjectionShadowDeform () ; 
 int /*<<< orphan*/  ShaderRequiresCPUDeforms (TYPE_5__*) ; 
 TYPE_4__ backEnd ; 
 TYPE_3__ tess ; 

void RB_DeformTessGeometry( void ) {
	int		i;
	deformStage_t	*ds;

	if(!ShaderRequiresCPUDeforms(tess.shader))
	{
		// we don't need the following CPU deforms
		return;
	}

	for ( i = 0 ; i < tess.shader->numDeforms ; i++ ) {
		ds = &tess.shader->deforms[ i ];

		switch ( ds->deformation ) {
        case DEFORM_NONE:
            break;
		case DEFORM_NORMALS:
			RB_CalcDeformNormals( ds );
			break;
		case DEFORM_WAVE:
			RB_CalcDeformVertexes( ds );
			break;
		case DEFORM_BULGE:
			RB_CalcBulgeVertexes( ds );
			break;
		case DEFORM_MOVE:
			RB_CalcMoveVertexes( ds );
			break;
		case DEFORM_PROJECTION_SHADOW:
			RB_ProjectionShadowDeform();
			break;
		case DEFORM_AUTOSPRITE:
			AutospriteDeform();
			break;
		case DEFORM_AUTOSPRITE2:
			Autosprite2Deform();
			break;
		case DEFORM_TEXT0:
		case DEFORM_TEXT1:
		case DEFORM_TEXT2:
		case DEFORM_TEXT3:
		case DEFORM_TEXT4:
		case DEFORM_TEXT5:
		case DEFORM_TEXT6:
		case DEFORM_TEXT7:
			DeformText( backEnd.refdef.text[ds->deformation - DEFORM_TEXT0] );
			break;
		}
	}
}