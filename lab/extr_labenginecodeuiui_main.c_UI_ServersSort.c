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
typedef  int /*<<< orphan*/  qboolean ;
struct TYPE_3__ {int sortKey; int /*<<< orphan*/  currentServer; int /*<<< orphan*/  numDisplayServers; int /*<<< orphan*/ * displayServers; } ;
struct TYPE_4__ {TYPE_1__ serverStatus; } ;

/* Variables and functions */
 int /*<<< orphan*/  FEEDER_SERVERS ; 
 int /*<<< orphan*/  UI_FeederSelection (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UI_ServersQsortCompare ; 
 int /*<<< orphan*/  qsort (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 TYPE_2__ uiInfo ; 

void UI_ServersSort(int column, qboolean force) {

	if ( !force ) {
		if ( uiInfo.serverStatus.sortKey == column ) {
			return;
		}
	}

	uiInfo.serverStatus.sortKey = column;
	qsort( &uiInfo.serverStatus.displayServers[0], uiInfo.serverStatus.numDisplayServers, sizeof(int), UI_ServersQsortCompare);

	// update displayed levelshot
	UI_FeederSelection( FEEDER_SERVERS, uiInfo.serverStatus.currentServer );
}