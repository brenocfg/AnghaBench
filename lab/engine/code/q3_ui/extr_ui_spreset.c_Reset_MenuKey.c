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
struct TYPE_2__ {int /*<<< orphan*/  menu; int /*<<< orphan*/  yes; int /*<<< orphan*/  no; } ;

/* Variables and functions */
#define  K_KP_LEFTARROW 131 
#define  K_KP_RIGHTARROW 130 
#define  K_LEFTARROW 129 
#define  K_RIGHTARROW 128 
 int K_TAB ; 
 int /*<<< orphan*/  Menu_DefaultKey (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  QM_ACTIVATED ; 
 int /*<<< orphan*/  Reset_MenuEvent (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__ s_reset ; 

__attribute__((used)) static sfxHandle_t Reset_MenuKey( int key ) {
	switch ( key ) {
	case K_KP_LEFTARROW:
	case K_LEFTARROW:
	case K_KP_RIGHTARROW:
	case K_RIGHTARROW:
		key = K_TAB;
		break;

	case 'n':
	case 'N':
		Reset_MenuEvent( &s_reset.no, QM_ACTIVATED );
		break;

	case 'y':
	case 'Y':
		Reset_MenuEvent( &s_reset.yes, QM_ACTIVATED );
		break;
	}

	return Menu_DefaultKey( &s_reset.menu, key );
}