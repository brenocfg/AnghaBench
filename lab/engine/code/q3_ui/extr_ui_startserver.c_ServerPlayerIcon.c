#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  model ;

/* Variables and functions */
 int /*<<< orphan*/  Com_sprintf (char*,int,char*,char*,...) ; 
 int MAX_QPATH ; 
 scalar_t__ Q_stricmp (char*,char*) ; 
 int /*<<< orphan*/  Q_strncpyz (char*,char const*,int) ; 
 char* strrchr (char*,char) ; 
 int /*<<< orphan*/  trap_R_RegisterShaderNoMip (char*) ; 

__attribute__((used)) static void ServerPlayerIcon( const char *modelAndSkin, char *iconName, int iconNameMaxSize ) {
	char	*skin;
	char	model[MAX_QPATH];

	Q_strncpyz( model, modelAndSkin, sizeof(model));
	skin = strrchr( model, '/' );
	if ( skin ) {
		*skin++ = '\0';
	}
	else {
		skin = "default";
	}

	Com_sprintf(iconName, iconNameMaxSize, "models/players/%s/icon_%s.tga", model, skin );

	if( !trap_R_RegisterShaderNoMip( iconName ) && Q_stricmp( skin, "default" ) != 0 ) {
		Com_sprintf(iconName, iconNameMaxSize, "models/players/%s/icon_default.tga", model );
	}
}