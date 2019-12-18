#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;
typedef  struct TYPE_12__   TYPE_11__ ;

/* Type definitions */
typedef  double* vec3_t ;
struct TYPE_15__ {float x; float y; float width; float height; float fov_x; float fov_y; scalar_t__ time; double* origin; double* lightingOrigin; int renderfx; double* oldorigin; int /*<<< orphan*/  hModel; int /*<<< orphan*/  axis; int /*<<< orphan*/  viewaxis; int /*<<< orphan*/  rdflags; } ;
typedef  TYPE_3__ refdef_t ;
typedef  int /*<<< orphan*/  refdef ;
typedef  TYPE_3__ refEntity_t ;
struct TYPE_16__ {float fov_x; float fov_y; scalar_t__ rotationSpeed; int angle; } ;
typedef  TYPE_5__ modelDef_t ;
struct TYPE_13__ {int x; int y; int w; int h; } ;
struct TYPE_14__ {scalar_t__ nextTime; TYPE_1__ rect; } ;
struct TYPE_17__ {double textscale; int /*<<< orphan*/  asset; TYPE_2__ window; scalar_t__ typeData; } ;
typedef  TYPE_6__ itemDef_t ;
typedef  int /*<<< orphan*/  ent ;
struct TYPE_12__ {scalar_t__ realTime; int /*<<< orphan*/  (* renderScene ) (TYPE_3__*) ;int /*<<< orphan*/  (* addRefEntityToScene ) (TYPE_3__*) ;int /*<<< orphan*/  (* clearScene ) () ;int /*<<< orphan*/  (* modelBounds ) (int /*<<< orphan*/ ,double*,double*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  AdjustFrom640 (float*,float*,float*,float*) ; 
 int /*<<< orphan*/  AnglesToAxis (double*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AxisClear (int /*<<< orphan*/ ) ; 
 TYPE_11__* DC ; 
 int /*<<< orphan*/  RDF_NOWORLDMODEL ; 
 int RF_LIGHTING_ORIGIN ; 
 int RF_NOSHADOW ; 
 int /*<<< orphan*/  VectorCopy (double*,double*) ; 
 int /*<<< orphan*/  VectorSet (double*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ qtrue ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,double*,double*) ; 
 int /*<<< orphan*/  stub2 () ; 
 int /*<<< orphan*/  stub3 (TYPE_3__*) ; 
 int /*<<< orphan*/  stub4 (TYPE_3__*) ; 

void Item_Model_Paint(itemDef_t *item) {
	float x, y, w, h;
	refdef_t refdef;
	refEntity_t		ent;
	vec3_t			mins, maxs, origin;
	vec3_t			angles;
	modelDef_t *modelPtr = (modelDef_t*)item->typeData;

	if (modelPtr == NULL) {
		return;
	}

	// setup the refdef
	memset( &refdef, 0, sizeof( refdef ) );
	refdef.rdflags = RDF_NOWORLDMODEL;
	AxisClear( refdef.viewaxis );
	x = item->window.rect.x+1;
	y = item->window.rect.y+1;
	w = item->window.rect.w-2;
	h = item->window.rect.h-2;

	AdjustFrom640( &x, &y, &w, &h );

	refdef.x = x;
	refdef.y = y;
	refdef.width = w;
	refdef.height = h;

	DC->modelBounds( item->asset, mins, maxs );

	origin[2] = -0.5 * ( mins[2] + maxs[2] );
	origin[1] = 0.5 * ( mins[1] + maxs[1] );

	// calculate distance so the model nearly fills the box
	if (qtrue) {
		float len = 0.5 * ( maxs[2] - mins[2] );		
		origin[0] = len / 0.268;	// len / tan( fov/2 )
		//origin[0] = len / tan(w/2);
	} else {
		origin[0] = item->textscale;
	}
	refdef.fov_x = (modelPtr->fov_x) ? modelPtr->fov_x : w;
	refdef.fov_y = (modelPtr->fov_y) ? modelPtr->fov_y : h;

	//refdef.fov_x = (int)((float)refdef.width / 640.0f * 90.0f);
	//xx = refdef.width / tan( refdef.fov_x / 360 * M_PI );
	//refdef.fov_y = atan2( refdef.height, xx );
	//refdef.fov_y *= ( 360 / M_PI );

	DC->clearScene();

	refdef.time = DC->realTime;

	// add the model

	memset( &ent, 0, sizeof(ent) );

	//adjust = 5.0 * sin( (float)uis.realtime / 500 );
	//adjust = 360 % (int)((float)uis.realtime / 1000);
	//VectorSet( angles, 0, 0, 1 );

	// use item storage to track
	if (modelPtr->rotationSpeed) {
		if (DC->realTime > item->window.nextTime) {
			item->window.nextTime = DC->realTime + modelPtr->rotationSpeed;
			modelPtr->angle = (int)(modelPtr->angle + 1) % 360;
		}
	}
	VectorSet( angles, 0, modelPtr->angle, 0 );
	AnglesToAxis( angles, ent.axis );

	ent.hModel = item->asset;
	VectorCopy( origin, ent.origin );
	VectorCopy( origin, ent.lightingOrigin );
	ent.renderfx = RF_LIGHTING_ORIGIN | RF_NOSHADOW;
	VectorCopy( ent.origin, ent.oldorigin );

	DC->addRefEntityToScene( &ent );
	DC->renderScene( &refdef );

}