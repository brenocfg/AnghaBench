#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ state; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* EndFrameCustomView ) () ;int /*<<< orphan*/  (* BeginFrameCustomView ) () ;} ;

/* Variables and functions */
 scalar_t__ CA_ACTIVE ; 
 int /*<<< orphan*/  CG_DRAW_CUSTOM_VIEW ; 
 int /*<<< orphan*/  VM_Call (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cgvm ; 
 TYPE_2__ clc ; 
 TYPE_1__ re ; 
 int /*<<< orphan*/  scr_initialized ; 
 int /*<<< orphan*/  stub1 () ; 
 int /*<<< orphan*/  stub2 () ; 
 int /*<<< orphan*/  uivm ; 

void SCR_RenderCustomView() {
	if ( !scr_initialized ) {
		return;				// not initialized yet
	}

	if ( !uivm || clc.state != CA_ACTIVE) {
		return;
	}
	re.BeginFrameCustomView( );
	VM_Call( cgvm, CG_DRAW_CUSTOM_VIEW );
	re.EndFrameCustomView( );
}