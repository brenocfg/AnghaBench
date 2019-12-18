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
typedef  int /*<<< orphan*/  sfxHandle_t ;
struct TYPE_3__ {int /*<<< orphan*/ * sounds; } ;
typedef  TYPE_1__ clientInfo_t ;
struct TYPE_4__ {TYPE_1__* clientinfo; } ;

/* Variables and functions */
 int /*<<< orphan*/  CG_Error (char*,char const*) ; 
 int MAX_CLIENTS ; 
 int MAX_CUSTOM_SOUNDS ; 
 scalar_t__* cg_customSoundNames ; 
 TYPE_2__ cgs ; 
 int /*<<< orphan*/  qfalse ; 
 int /*<<< orphan*/  strcmp (char const*,scalar_t__) ; 
 int /*<<< orphan*/  trap_S_RegisterSound (char const*,int /*<<< orphan*/ ) ; 

sfxHandle_t	CG_CustomSound( int clientNum, const char *soundName ) {
	clientInfo_t *ci;
	int			i;

	if ( soundName[0] != '*' ) {
		return trap_S_RegisterSound( soundName, qfalse );
	}

	if ( clientNum < 0 || clientNum >= MAX_CLIENTS ) {
		clientNum = 0;
	}
	ci = &cgs.clientinfo[ clientNum ];

	for ( i = 0 ; i < MAX_CUSTOM_SOUNDS && cg_customSoundNames[i] ; i++ ) {
		if ( !strcmp( soundName, cg_customSoundNames[i] ) ) {
			return ci->sounds[i];
		}
	}

	CG_Error( "Unknown custom sound: %s", soundName );
	return 0;
}