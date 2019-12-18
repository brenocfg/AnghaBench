#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int id; } ;
typedef  TYPE_5__ menucommon_s ;
struct TYPE_10__ {int /*<<< orphan*/  curvalue; } ;
struct TYPE_9__ {int /*<<< orphan*/  curvalue; } ;
struct TYPE_8__ {int curvalue; } ;
struct TYPE_7__ {int curvalue; } ;
struct TYPE_12__ {int sfxvolume_original; int musicvolume_original; TYPE_4__ soundSystem; int /*<<< orphan*/  soundSystem_original; TYPE_3__ quality; int /*<<< orphan*/  quality_original; TYPE_2__ musicvolume; TYPE_1__ sfxvolume; } ;

/* Variables and functions */
 int DEFAULT_SDL_SND_SPEED ; 
 int /*<<< orphan*/  EXEC_APPEND ; 
#define  ID_APPLY 133 
#define  ID_BACK 132 
#define  ID_DISPLAY 131 
#define  ID_GRAPHICS 130 
#define  ID_NETWORK 129 
#define  ID_SOUND 128 
 int QM_ACTIVATED ; 
 int /*<<< orphan*/  UISND_OPENAL ; 
 int /*<<< orphan*/  UI_DisplayOptionsMenu () ; 
 int /*<<< orphan*/  UI_ForceMenuOff () ; 
 int /*<<< orphan*/  UI_GraphicsOptionsMenu () ; 
 int /*<<< orphan*/  UI_NetworkOptionsMenu () ; 
 int /*<<< orphan*/  UI_PopMenu () ; 
 TYPE_6__ soundOptionsInfo ; 
 int /*<<< orphan*/  trap_Cmd_ExecuteText (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  trap_Cvar_SetValue (char*,int) ; 

__attribute__((used)) static void UI_SoundOptionsMenu_Event( void* ptr, int event ) {
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
		break;

	case ID_NETWORK:
		UI_PopMenu();
		UI_NetworkOptionsMenu();
		break;
/*
	case ID_A3D:
		if( soundOptionsInfo.a3d.curvalue ) {
			trap_Cmd_ExecuteText( EXEC_NOW, "s_enable_a3d\n" );
		}
		else {
			trap_Cmd_ExecuteText( EXEC_NOW, "s_disable_a3d\n" );
		}
		soundOptionsInfo.a3d.curvalue = (int)trap_Cvar_VariableValue( "s_usingA3D" );
		break;
*/
	case ID_BACK:
		UI_PopMenu();
		break;

	case ID_APPLY:
		trap_Cvar_SetValue( "s_volume", soundOptionsInfo.sfxvolume.curvalue / 10 );
		soundOptionsInfo.sfxvolume_original = soundOptionsInfo.sfxvolume.curvalue;

		trap_Cvar_SetValue( "s_musicvolume", soundOptionsInfo.musicvolume.curvalue / 10 );
		soundOptionsInfo.musicvolume_original = soundOptionsInfo.musicvolume.curvalue;

		// Check if something changed that requires the sound system to be restarted.
		if (soundOptionsInfo.quality_original != soundOptionsInfo.quality.curvalue
			|| soundOptionsInfo.soundSystem_original != soundOptionsInfo.soundSystem.curvalue)
		{
			int speed;

			switch ( soundOptionsInfo.quality.curvalue )
			{
				default:
				case 0:
					speed = 11025;
					break;
				case 1:
					speed = 22050;
					break;
				case 2:
					speed = 44100;
					break;
			}

			if (speed == DEFAULT_SDL_SND_SPEED)
				speed = 0;

			trap_Cvar_SetValue( "s_sdlSpeed", speed );
			soundOptionsInfo.quality_original = soundOptionsInfo.quality.curvalue;

			trap_Cvar_SetValue( "s_useOpenAL", (soundOptionsInfo.soundSystem.curvalue == UISND_OPENAL) );
			soundOptionsInfo.soundSystem_original = soundOptionsInfo.soundSystem.curvalue;

			UI_ForceMenuOff();
			trap_Cmd_ExecuteText( EXEC_APPEND, "snd_restart\n" );
		}
		break;
	}
}