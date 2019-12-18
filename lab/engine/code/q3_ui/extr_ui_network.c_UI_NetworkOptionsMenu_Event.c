#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int id; } ;
typedef  TYPE_2__ menucommon_s ;
struct TYPE_4__ {int curvalue; } ;
struct TYPE_6__ {TYPE_1__ rate; } ;

/* Variables and functions */
#define  ID_BACK 133 
#define  ID_DISPLAY 132 
#define  ID_GRAPHICS 131 
#define  ID_NETWORK 130 
#define  ID_RATE 129 
#define  ID_SOUND 128 
 int QM_ACTIVATED ; 
 int /*<<< orphan*/  UI_DisplayOptionsMenu () ; 
 int /*<<< orphan*/  UI_GraphicsOptionsMenu () ; 
 int /*<<< orphan*/  UI_PopMenu () ; 
 int /*<<< orphan*/  UI_SoundOptionsMenu () ; 
 TYPE_3__ networkOptionsInfo ; 
 int /*<<< orphan*/  trap_Cvar_SetValue (char*,int) ; 

__attribute__((used)) static void UI_NetworkOptionsMenu_Event( void* ptr, int event ) {
	if( event != QM_ACTIVATED ) {
		return;
	}

	switch( ((menucommon_s*)ptr)->id ) {
	case ID_GRAPHICS:
		UI_PopMenu();
		UI_GraphicsOptionsMenu();
		break;

	case ID_DISPLAY:
		UI_PopMenu();
		UI_DisplayOptionsMenu();
		break;

	case ID_SOUND:
		UI_PopMenu();
		UI_SoundOptionsMenu();
		break;

	case ID_NETWORK:
		break;

	case ID_RATE:
		if( networkOptionsInfo.rate.curvalue == 0 ) {
			trap_Cvar_SetValue( "rate", 2500 );
		}
		else if( networkOptionsInfo.rate.curvalue == 1 ) {
			trap_Cvar_SetValue( "rate", 3000 );
		}
		else if( networkOptionsInfo.rate.curvalue == 2 ) {
			trap_Cvar_SetValue( "rate", 4000 );
		}
		else if( networkOptionsInfo.rate.curvalue == 3 ) {
			trap_Cvar_SetValue( "rate", 5000 );
		}
		else if( networkOptionsInfo.rate.curvalue == 4 ) {
			trap_Cvar_SetValue( "rate", 25000 );
		}
		break;

	case ID_BACK:
		UI_PopMenu();
		break;
	}
}