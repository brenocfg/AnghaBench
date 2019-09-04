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
struct TYPE_6__ {int spectatorLen; int spectatorWidth; scalar_t__* spectatorList; } ;
struct TYPE_5__ {TYPE_1__* clientinfo; } ;
struct TYPE_4__ {scalar_t__ team; int /*<<< orphan*/  name; scalar_t__ infoValid; } ;

/* Variables and functions */
 int MAX_CLIENTS ; 
 int /*<<< orphan*/  Q_strcat (scalar_t__*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ TEAM_SPECTATOR ; 
 TYPE_3__ cg ; 
 TYPE_2__ cgs ; 
 int strlen (scalar_t__*) ; 
 int /*<<< orphan*/  va (char*,int /*<<< orphan*/ ) ; 

void CG_BuildSpectatorString(void) {
	int i;
	cg.spectatorList[0] = 0;
	for (i = 0; i < MAX_CLIENTS; i++) {
		if (cgs.clientinfo[i].infoValid && cgs.clientinfo[i].team == TEAM_SPECTATOR ) {
			Q_strcat(cg.spectatorList, sizeof(cg.spectatorList), va("%s     ", cgs.clientinfo[i].name));
		}
	}
	i = strlen(cg.spectatorList);
	if (i != cg.spectatorLen) {
		cg.spectatorLen = i;
		cg.spectatorWidth = -1;
	}
}