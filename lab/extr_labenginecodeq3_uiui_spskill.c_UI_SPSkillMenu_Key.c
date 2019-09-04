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
typedef  int /*<<< orphan*/  sfxHandle_t ;
struct TYPE_2__ {int /*<<< orphan*/  menu; int /*<<< orphan*/  silenceSound; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHAN_ANNOUNCER ; 
 int K_ESCAPE ; 
 int K_MOUSE2 ; 
 int /*<<< orphan*/  Menu_DefaultKey (int /*<<< orphan*/ *,int) ; 
 TYPE_1__ skillMenuInfo ; 
 int /*<<< orphan*/  trap_S_StartLocalSound (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static sfxHandle_t UI_SPSkillMenu_Key( int key ) {
	if( key == K_MOUSE2 || key == K_ESCAPE ) {
		trap_S_StartLocalSound( skillMenuInfo.silenceSound, CHAN_ANNOUNCER );
	}
	return Menu_DefaultKey( &skillMenuInfo.menu, key );
}