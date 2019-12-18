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
#define  ID_BACK 133 
#define  ID_DEDICATED 132 
#define  ID_GO 131 
#define  ID_MAXCLIENTS 130 
#define  ID_PLAYER_TYPE 129 
#define  ID_STARTSERVERNEXT 128 
 int QM_ACTIVATED ; 
 int /*<<< orphan*/  ServerOptions_SetPlayerItems () ; 
 int /*<<< orphan*/  ServerOptions_Start () ; 
 int /*<<< orphan*/  UI_PopMenu () ; 

__attribute__((used)) static void ServerOptions_Event( void* ptr, int event ) {
	switch( ((menucommon_s*)ptr)->id ) {
	
	//if( event != QM_ACTIVATED && event != QM_LOSTFOCUS) {
	//	return;
	//}
	case ID_PLAYER_TYPE:
		if( event != QM_ACTIVATED ) {
			break;
		}
		ServerOptions_SetPlayerItems();
		break;

	case ID_MAXCLIENTS:
	case ID_DEDICATED:
		ServerOptions_SetPlayerItems();
		break;
	case ID_GO:
		if( event != QM_ACTIVATED ) {
			break;
		}
		ServerOptions_Start();
		break;

	case ID_STARTSERVERNEXT:
		if( event != QM_ACTIVATED ) {
			break;
		}
		break;
	case ID_BACK:
		if( event != QM_ACTIVATED ) {
			break;
		}
		UI_PopMenu();
		break;
	}
}