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
struct TYPE_3__ {int numDisplayServers; int* displayServers; int currentServer; } ;
struct TYPE_4__ {TYPE_1__ serverStatus; } ;

/* Variables and functions */
 int /*<<< orphan*/  FEEDER_SERVERS ; 
 int /*<<< orphan*/  UI_FeederSelection (int /*<<< orphan*/ ,int) ; 
 TYPE_2__ uiInfo ; 

__attribute__((used)) static void UI_InsertServerIntoDisplayList(int num, int position) {
	int i;

	if (position < 0 || position > uiInfo.serverStatus.numDisplayServers ) {
		return;
	}
	//
	uiInfo.serverStatus.numDisplayServers++;
	for (i = uiInfo.serverStatus.numDisplayServers; i > position; i--) {
		uiInfo.serverStatus.displayServers[i] = uiInfo.serverStatus.displayServers[i-1];
	}
	uiInfo.serverStatus.displayServers[position] = num;

	// update displayed levelshot
	if ( position == uiInfo.serverStatus.currentServer ) {
		UI_FeederSelection( FEEDER_SERVERS, uiInfo.serverStatus.currentServer );
	}
}