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
struct TYPE_2__ {int* mouseDx; size_t mouseIndex; int* mouseDy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CG_MOUSE_EVENT ; 
 int KEYCATCH_CGAME ; 
 int KEYCATCH_UI ; 
 int Key_GetCatcher () ; 
 int /*<<< orphan*/  UI_MOUSE_EVENT ; 
 int /*<<< orphan*/  VM_Call (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  cgvm ; 
 TYPE_1__ cl ; 
 int /*<<< orphan*/  uivm ; 

void CL_MouseEvent( int dx, int dy, int time ) {
	if ( Key_GetCatcher( ) & KEYCATCH_UI ) {
		VM_Call( uivm, UI_MOUSE_EVENT, dx, dy );
	} else if (Key_GetCatcher( ) & KEYCATCH_CGAME) {
		VM_Call (cgvm, CG_MOUSE_EVENT, dx, dy);
	} else {
		cl.mouseDx[cl.mouseIndex] += dx;
		cl.mouseDy[cl.mouseIndex] += dy;
	}
}