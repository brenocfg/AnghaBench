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
typedef  int /*<<< orphan*/  qboolean ;
struct TYPE_2__ {scalar_t__ integer; } ;

/* Variables and functions */
 int /*<<< orphan*/  UI_BuildServerDisplayList (int /*<<< orphan*/ ) ; 
 int UI_SelectForKey (int) ; 
 scalar_t__ numServerFilters ; 
 int /*<<< orphan*/  qfalse ; 
 int /*<<< orphan*/  qtrue ; 
 TYPE_1__ ui_serverFilterType ; 

__attribute__((used)) static qboolean UI_NetFilter_HandleKey(int flags, float *special, int key) {
	int select = UI_SelectForKey(key);
	if (select != 0) {
		ui_serverFilterType.integer += select;

		if (ui_serverFilterType.integer >= numServerFilters) {
			ui_serverFilterType.integer = 0;
		} else if (ui_serverFilterType.integer < 0) {
			ui_serverFilterType.integer = numServerFilters - 1;
		}
		UI_BuildServerDisplayList(qtrue);
		return qtrue;
	}
	return qfalse;
}