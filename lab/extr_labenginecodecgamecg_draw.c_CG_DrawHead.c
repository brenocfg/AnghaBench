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
typedef  double* vec3_t ;
typedef  int /*<<< orphan*/  clipHandle_t ;
struct TYPE_7__ {scalar_t__ deferred; int /*<<< orphan*/  modelIcon; int /*<<< orphan*/  headSkin; int /*<<< orphan*/  headModel; int /*<<< orphan*/  headOffset; } ;
typedef  TYPE_2__ clientInfo_t ;
struct TYPE_10__ {scalar_t__ integer; } ;
struct TYPE_9__ {scalar_t__ integer; } ;
struct TYPE_6__ {int /*<<< orphan*/  deferShader; } ;
struct TYPE_8__ {TYPE_1__ media; TYPE_2__* clientinfo; } ;

/* Variables and functions */
 int /*<<< orphan*/  CG_Draw3DModel (float,float,float,float,int /*<<< orphan*/ ,int /*<<< orphan*/ ,double*,double*) ; 
 int /*<<< orphan*/  CG_DrawPic (float,float,float,float,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VectorAdd (double*,int /*<<< orphan*/ ,double*) ; 
 TYPE_5__ cg_draw3dIcons ; 
 TYPE_4__ cg_drawIcons ; 
 TYPE_3__ cgs ; 
 int /*<<< orphan*/  trap_R_ModelBounds (int /*<<< orphan*/ ,double*,double*) ; 

void CG_DrawHead( float x, float y, float w, float h, int clientNum, vec3_t headAngles ) {
	clipHandle_t	cm;
	clientInfo_t	*ci;
	float			len;
	vec3_t			origin;
	vec3_t			mins, maxs;

	ci = &cgs.clientinfo[ clientNum ];

	if ( cg_draw3dIcons.integer ) {
		cm = ci->headModel;
		if ( !cm ) {
			return;
		}

		// offset the origin y and z to center the head
		trap_R_ModelBounds( cm, mins, maxs );

		origin[2] = -0.5 * ( mins[2] + maxs[2] );
		origin[1] = 0.5 * ( mins[1] + maxs[1] );

		// calculate distance so the head nearly fills the box
		// assume heads are taller than wide
		len = 0.7 * ( maxs[2] - mins[2] );		
		origin[0] = len / 0.268;	// len / tan( fov/2 )

		// allow per-model tweaking
		VectorAdd( origin, ci->headOffset, origin );

		CG_Draw3DModel( x, y, w, h, ci->headModel, ci->headSkin, origin, headAngles );
	} else if ( cg_drawIcons.integer ) {
		CG_DrawPic( x, y, w, h, ci->modelIcon );
	}

	// if they are deferred, draw a cross out
	if ( ci->deferred ) {
		CG_DrawPic( x, y, w, h, cgs.media.deferShader );
	}
}