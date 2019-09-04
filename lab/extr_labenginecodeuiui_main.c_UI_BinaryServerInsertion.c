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
struct TYPE_3__ {int numDisplayServers; int /*<<< orphan*/ * displayServers; int /*<<< orphan*/  sortDir; int /*<<< orphan*/  sortKey; } ;
struct TYPE_4__ {TYPE_1__ serverStatus; } ;

/* Variables and functions */
 int /*<<< orphan*/  UI_InsertServerIntoDisplayList (int,int) ; 
 int /*<<< orphan*/  UI_SourceForLAN () ; 
 int trap_LAN_CompareServers (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 TYPE_2__ uiInfo ; 

__attribute__((used)) static void UI_BinaryServerInsertion(int num) {
	int mid, offset, res, len;

	// use binary search to insert server
	len = uiInfo.serverStatus.numDisplayServers;
	mid = len;
	offset = 0;
	res = 0;
	while(mid > 0) {
		mid = len >> 1;
		//
		res = trap_LAN_CompareServers( UI_SourceForLAN(), uiInfo.serverStatus.sortKey,
					uiInfo.serverStatus.sortDir, num, uiInfo.serverStatus.displayServers[offset+mid]);
		// if equal
		if (res == 0) {
			UI_InsertServerIntoDisplayList(num, offset+mid);
			return;
		}
		// if larger
		else if (res == 1) {
			offset += mid;
			len -= mid;
		}
		// if smaller
		else {
			len -= mid;
		}
	}
	if (res == 1) {
		offset++;
	}
	UI_InsertServerIntoDisplayList(num, offset);
}