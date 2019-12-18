#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_33__   TYPE_9__ ;
typedef  struct TYPE_32__   TYPE_8__ ;
typedef  struct TYPE_31__   TYPE_7__ ;
typedef  struct TYPE_30__   TYPE_6__ ;
typedef  struct TYPE_29__   TYPE_5__ ;
typedef  struct TYPE_28__   TYPE_4__ ;
typedef  struct TYPE_27__   TYPE_3__ ;
typedef  struct TYPE_26__   TYPE_2__ ;
typedef  struct TYPE_25__   TYPE_1__ ;
typedef  struct TYPE_24__   TYPE_12__ ;
typedef  struct TYPE_23__   TYPE_11__ ;
typedef  struct TYPE_22__   TYPE_10__ ;

/* Type definitions */
struct TYPE_28__ {int renderfx; scalar_t__ customSkin; scalar_t__ customShader; int /*<<< orphan*/  oldframe; int /*<<< orphan*/  frame; } ;
struct TYPE_29__ {TYPE_4__ e; } ;
typedef  TYPE_5__ trRefEntity_t ;
struct TYPE_30__ {TYPE_8__* shader; int /*<<< orphan*/  name; } ;
typedef  TYPE_6__ srfIQModel_t ;
struct TYPE_31__ {int numSurfaces; TYPE_3__* surfaces; } ;
typedef  TYPE_7__ skin_t ;
struct TYPE_32__ {scalar_t__ sort; } ;
typedef  TYPE_8__ shader_t ;
typedef  int qboolean ;
struct TYPE_33__ {int num_surfaces; int /*<<< orphan*/  num_frames; TYPE_6__* surfaces; } ;
typedef  TYPE_9__ iqmData_t ;
struct TYPE_27__ {TYPE_8__* shader; int /*<<< orphan*/  name; } ;
struct TYPE_26__ {int /*<<< orphan*/  name; TYPE_9__* modelData; } ;
struct TYPE_25__ {int /*<<< orphan*/  isPortal; } ;
struct TYPE_24__ {int integer; } ;
struct TYPE_23__ {int /*<<< orphan*/  (* Printf ) (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_22__ {scalar_t__ numSkins; TYPE_8__* projectionShadowShader; TYPE_8__* shadowShader; TYPE_8__* defaultShader; int /*<<< orphan*/  refdef; TYPE_2__* currentModel; TYPE_1__ viewParms; } ;

/* Variables and functions */
 int CULL_OUT ; 
 int /*<<< orphan*/  PRINT_DEVELOPER ; 
 int RF_DEPTHHACK ; 
 int RF_NOSHADOW ; 
 int RF_SHADOW_PLANE ; 
 int RF_THIRD_PERSON ; 
 int RF_WRAP_FRAMES ; 
 int /*<<< orphan*/  R_AddDrawSurf (void*,TYPE_8__*,int,int /*<<< orphan*/ ) ; 
 int R_ComputeIQMFogNum (TYPE_9__*,TYPE_5__*) ; 
 int R_CullIQM (TYPE_9__*,TYPE_5__*) ; 
 TYPE_8__* R_GetShaderByHandle (scalar_t__) ; 
 TYPE_7__* R_GetSkinByHandle (scalar_t__) ; 
 int /*<<< orphan*/  R_SetupEntityLighting (int /*<<< orphan*/ *,TYPE_5__*) ; 
 scalar_t__ SS_OPAQUE ; 
 TYPE_12__* r_shadows ; 
 TYPE_11__ ri ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_10__ tr ; 

void R_AddIQMSurfaces( trRefEntity_t *ent ) {
	iqmData_t		*data;
	srfIQModel_t		*surface;
	int			i, j;
	qboolean		personalModel;
	int			cull;
	int			fogNum;
	shader_t		*shader;
	skin_t			*skin;

	data = tr.currentModel->modelData;
	surface = data->surfaces;

	// don't add third_person objects if not in a portal
	personalModel = (ent->e.renderfx & RF_THIRD_PERSON) && !tr.viewParms.isPortal;

	if ( ent->e.renderfx & RF_WRAP_FRAMES ) {
		ent->e.frame %= data->num_frames;
		ent->e.oldframe %= data->num_frames;
	}

	//
	// Validate the frames so there is no chance of a crash.
	// This will write directly into the entity structure, so
	// when the surfaces are rendered, they don't need to be
	// range checked again.
	//
	if ( (ent->e.frame >= data->num_frames) 
	     || (ent->e.frame < 0)
	     || (ent->e.oldframe >= data->num_frames)
	     || (ent->e.oldframe < 0) ) {
		ri.Printf( PRINT_DEVELOPER, "R_AddIQMSurfaces: no such frame %d to %d for '%s'\n",
			   ent->e.oldframe, ent->e.frame,
			   tr.currentModel->name );
		ent->e.frame = 0;
		ent->e.oldframe = 0;
	}

	//
	// cull the entire model if merged bounding box of both frames
	// is outside the view frustum.
	//
	cull = R_CullIQM ( data, ent );
	if ( cull == CULL_OUT ) {
		return;
	}

	//
	// set up lighting now that we know we aren't culled
	//
	if ( !personalModel || r_shadows->integer > 1 ) {
		R_SetupEntityLighting( &tr.refdef, ent );
	}

	//
	// see if we are in a fog volume
	//
	fogNum = R_ComputeIQMFogNum( data, ent );

	for ( i = 0 ; i < data->num_surfaces ; i++ ) {
		if(ent->e.customShader)
			shader = R_GetShaderByHandle( ent->e.customShader );
		else if(ent->e.customSkin > 0 && ent->e.customSkin < tr.numSkins)
		{
			skin = R_GetSkinByHandle(ent->e.customSkin);
			shader = tr.defaultShader;

			for(j = 0; j < skin->numSurfaces; j++)
			{
				if (!strcmp(skin->surfaces[j].name, surface->name))
				{
					shader = skin->surfaces[j].shader;
					break;
				}
			}
		} else {
			shader = surface->shader;
		}

		// we will add shadows even if the main object isn't visible in the view

		// stencil shadows can't do personal models unless I polyhedron clip
		if ( !personalModel
			&& r_shadows->integer == 2 
			&& fogNum == 0
			&& !(ent->e.renderfx & ( RF_NOSHADOW | RF_DEPTHHACK ) ) 
			&& shader->sort == SS_OPAQUE ) {
			R_AddDrawSurf( (void *)surface, tr.shadowShader, 0, 0 );
		}

		// projection shadows work fine with personal models
		if ( r_shadows->integer == 3
			&& fogNum == 0
			&& (ent->e.renderfx & RF_SHADOW_PLANE )
			&& shader->sort == SS_OPAQUE ) {
			R_AddDrawSurf( (void *)surface, tr.projectionShadowShader, 0, 0 );
		}

		if( !personalModel ) {
			R_AddDrawSurf( (void *)surface, shader, fogNum, 0 );
		}

		surface++;
	}
}