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
typedef  int /*<<< orphan*/  personality ;
typedef  int /*<<< orphan*/  model ;
struct TYPE_2__ {scalar_t__ gametype; } ;

/* Variables and functions */
 char* CG_ConfigString (scalar_t__) ; 
 int /*<<< orphan*/  CG_LoadingString (char*) ; 
 scalar_t__ CS_PLAYERS ; 
 int /*<<< orphan*/  Com_sprintf (char*,int,char*,char*,char*) ; 
 char* DEFAULT_MODEL ; 
 scalar_t__ GT_SINGLE_PLAYER ; 
 int /*<<< orphan*/  Info_ValueForKey (char const*,char*) ; 
 size_t MAX_LOADING_PLAYER_ICONS ; 
 int MAX_QPATH ; 
 int /*<<< orphan*/  Q_CleanStr (char*) ; 
 int /*<<< orphan*/  Q_strncpyz (char*,int /*<<< orphan*/ ,int) ; 
 TYPE_1__ cgs ; 
 size_t loadingPlayerIconCount ; 
 scalar_t__* loadingPlayerIcons ; 
 int /*<<< orphan*/  qtrue ; 
 char* strrchr (char*,char) ; 
 scalar_t__ trap_R_RegisterShaderNoMip (char*) ; 
 int /*<<< orphan*/  trap_S_RegisterSound (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  va (char*,char*) ; 

void CG_LoadingClient( int clientNum ) {
	const char		*info;
	char			*skin;
	char			personality[MAX_QPATH];
	char			model[MAX_QPATH];
	char			iconName[MAX_QPATH];

	info = CG_ConfigString( CS_PLAYERS + clientNum );

	if ( loadingPlayerIconCount < MAX_LOADING_PLAYER_ICONS ) {
		Q_strncpyz( model, Info_ValueForKey( info, "model" ), sizeof( model ) );
		skin = strrchr( model, '/' );
		if ( skin ) {
			*skin++ = '\0';
		} else {
			skin = "default";
		}

		Com_sprintf( iconName, MAX_QPATH, "models/players/%s/icon_%s.tga", model, skin );
		
		loadingPlayerIcons[loadingPlayerIconCount] = trap_R_RegisterShaderNoMip( iconName );
		if ( !loadingPlayerIcons[loadingPlayerIconCount] ) {
			Com_sprintf( iconName, MAX_QPATH, "models/players/characters/%s/icon_%s.tga", model, skin );
			loadingPlayerIcons[loadingPlayerIconCount] = trap_R_RegisterShaderNoMip( iconName );
		}
		if ( !loadingPlayerIcons[loadingPlayerIconCount] ) {
			Com_sprintf( iconName, MAX_QPATH, "models/players/%s/icon_%s.tga", DEFAULT_MODEL, "default" );
			loadingPlayerIcons[loadingPlayerIconCount] = trap_R_RegisterShaderNoMip( iconName );
		}
		if ( loadingPlayerIcons[loadingPlayerIconCount] ) {
			loadingPlayerIconCount++;
		}
	}

	Q_strncpyz( personality, Info_ValueForKey( info, "n" ), sizeof(personality) );
	Q_CleanStr( personality );

	if( cgs.gametype == GT_SINGLE_PLAYER ) {
		trap_S_RegisterSound( va( "sound/player/announce/%s.wav", personality ), qtrue );
	}

	CG_LoadingString( personality );
}