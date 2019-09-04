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
struct TYPE_2__ {int id; } ;
typedef  TYPE_1__ menucommon_s ;

/* Variables and functions */
#define  ID_BACK 132 
#define  ID_DISPLAY 131 
#define  ID_GRAPHICS 130 
#define  ID_NETWORK 129 
#define  ID_SOUND 128 
 int QM_ACTIVATED ; 
 int /*<<< orphan*/  UI_DisplayOptionsMenu () ; 
 int /*<<< orphan*/  UI_GraphicsOptionsMenu () ; 
 int /*<<< orphan*/  UI_NetworkOptionsMenu () ; 
 int /*<<< orphan*/  UI_PopMenu () ; 
 int /*<<< orphan*/  UI_SoundOptionsMenu () ; 

__attribute__((used)) static void Options_Event( void* ptr, int event ) {
	if( event != QM_ACTIVATED ) {
		return;
	}

	switch( ((menucommon_s*)ptr)->id ) {
	case ID_GRAPHICS:
		UI_GraphicsOptionsMenu();
		break;

	case ID_DISPLAY:
		UI_DisplayOptionsMenu();
		break;

	case ID_SOUND:
		UI_SoundOptionsMenu();
		break;

	case ID_NETWORK:
		UI_NetworkOptionsMenu();
		break;

	case ID_BACK:
		UI_PopMenu();
		break;
	}
}