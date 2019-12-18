#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ realTime; } ;
struct TYPE_4__ {scalar_t__ refreshtime; int /*<<< orphan*/  refreshActive; } ;
struct TYPE_6__ {TYPE_2__ uiDC; TYPE_1__ serverStatus; } ;

/* Variables and functions */
 int /*<<< orphan*/  UI_SourceForLAN () ; 
 int /*<<< orphan*/  qtrue ; 
 int /*<<< orphan*/  trap_LAN_ResetPings (int /*<<< orphan*/ ) ; 
 TYPE_3__ uiInfo ; 

__attribute__((used)) static void UI_UpdatePendingPings( void ) { 
	trap_LAN_ResetPings(UI_SourceForLAN());
	uiInfo.serverStatus.refreshActive = qtrue;
	uiInfo.serverStatus.refreshtime = uiInfo.uiDC.realTime + 1000;

}