#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  cmodel_t ;
typedef  size_t clipHandle_t ;
struct TYPE_2__ {size_t numSubModels; int /*<<< orphan*/ * cmodels; } ;

/* Variables and functions */
 size_t BOX_MODEL_HANDLE ; 
 int /*<<< orphan*/  Com_Error (int /*<<< orphan*/ ,char*,size_t,...) ; 
 int /*<<< orphan*/  ERR_DROP ; 
 size_t MAX_SUBMODELS ; 
 int /*<<< orphan*/  box_model ; 
 TYPE_1__ cm ; 

cmodel_t	*CM_ClipHandleToModel( clipHandle_t handle ) {
	if ( handle < 0 ) {
		Com_Error( ERR_DROP, "CM_ClipHandleToModel: bad handle %i", handle );
	}
	if ( handle < cm.numSubModels ) {
		return &cm.cmodels[handle];
	}
	if ( handle == BOX_MODEL_HANDLE ) {
		return &box_model;
	}
	if ( handle < MAX_SUBMODELS ) {
		Com_Error( ERR_DROP, "CM_ClipHandleToModel: bad handle %i < %i < %i", 
			cm.numSubModels, handle, MAX_SUBMODELS );
	}
	Com_Error( ERR_DROP, "CM_ClipHandleToModel: bad handle %i", handle + MAX_SUBMODELS );

	return NULL;

}