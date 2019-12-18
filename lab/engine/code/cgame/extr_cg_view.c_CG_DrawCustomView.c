#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  time; } ;
struct TYPE_7__ {TYPE_2__ refdef; int /*<<< orphan*/  renderingThirdPerson; int /*<<< orphan*/  time; TYPE_1__* snap; } ;
struct TYPE_5__ {int snapFlags; } ;

/* Variables and functions */
 int /*<<< orphan*/  CG_AddLocalEntities () ; 
 int /*<<< orphan*/  CG_AddMarks () ; 
 int /*<<< orphan*/  CG_AddPacketEntities () ; 
 int /*<<< orphan*/  CG_AddParticles () ; 
 int SNAPFLAG_NOT_ACTIVE ; 
 TYPE_4__ cg ; 
 int /*<<< orphan*/  dmlab_custom_view (TYPE_2__*) ; 
 int /*<<< orphan*/  trap_R_ClearScene () ; 
 int /*<<< orphan*/  trap_R_RenderScene (TYPE_2__*) ; 

void CG_DrawCustomView() {
	trap_R_ClearScene();
	if ( !cg.snap || ( cg.snap->snapFlags & SNAPFLAG_NOT_ACTIVE ) ) {
		return;
	}
	cg.refdef.time = cg.time;
	cg.renderingThirdPerson = dmlab_custom_view( &cg.refdef );
	CG_AddPacketEntities();
	CG_AddMarks();
	CG_AddParticles();
	CG_AddLocalEntities();

	// actually issue the rendering calls
	trap_R_RenderScene( &cg.refdef );
}