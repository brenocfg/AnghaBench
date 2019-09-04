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
typedef  int /*<<< orphan*/  qboolean ;
struct TYPE_3__ {scalar_t__ id; } ;
typedef  TYPE_1__ menucommon_s ;
struct TYPE_4__ {int /*<<< orphan*/  (* action ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 scalar_t__ ID_CONFIRM_NO ; 
 int QM_ACTIVATED ; 
 int /*<<< orphan*/  UI_PopMenu () ; 
 int /*<<< orphan*/  qfalse ; 
 int /*<<< orphan*/  qtrue ; 
 TYPE_2__ s_confirm ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ConfirmMenu_Event( void* ptr, int event ) {
	qboolean	result;

	if( event != QM_ACTIVATED ) {
		return;
	}

	UI_PopMenu();

	if( ((menucommon_s*)ptr)->id == ID_CONFIRM_NO ) {
		result = qfalse;
	}
	else {
		result = qtrue;
	}

	if( s_confirm.action ) {
		s_confirm.action( result );
	}
}