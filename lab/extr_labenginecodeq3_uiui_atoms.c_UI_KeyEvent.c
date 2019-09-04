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
typedef  scalar_t__ sfxHandle_t ;
struct TYPE_4__ {scalar_t__ (* key ) (int) ;} ;
struct TYPE_3__ {TYPE_2__* activemenu; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHAN_LOCAL_SOUND ; 
 scalar_t__ Menu_DefaultKey (TYPE_2__*,int) ; 
 scalar_t__ menu_null_sound ; 
 scalar_t__ stub1 (int) ; 
 int /*<<< orphan*/  trap_S_StartLocalSound (scalar_t__,int /*<<< orphan*/ ) ; 
 TYPE_1__ uis ; 

void UI_KeyEvent( int key, int down ) {
	sfxHandle_t		s;

	if (!uis.activemenu) {
		return;
	}

	if (!down) {
		return;
	}

	if (uis.activemenu->key)
		s = uis.activemenu->key( key );
	else
		s = Menu_DefaultKey( uis.activemenu, key );

	if ((s > 0) && (s != menu_null_sound))
		trap_S_StartLocalSound( s, CHAN_LOCAL_SOUND );
}