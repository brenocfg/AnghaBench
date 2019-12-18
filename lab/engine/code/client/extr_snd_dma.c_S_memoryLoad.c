#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {void* inMemory; void* defaultSound; } ;
typedef  TYPE_1__ sfx_t ;

/* Variables and functions */
 int /*<<< orphan*/  S_LoadSound (TYPE_1__*) ; 
 void* qtrue ; 

void S_memoryLoad(sfx_t	*sfx) {
	// load the sound file
	if ( !S_LoadSound ( sfx ) ) {
//		Com_Printf( S_COLOR_YELLOW "WARNING: couldn't load sound: %s\n", sfx->soundName );
		sfx->defaultSound = qtrue;
	}
	sfx->inMemory = qtrue;
}