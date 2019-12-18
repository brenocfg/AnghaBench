#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  netname ;
struct TYPE_3__ {char* teamleader; } ;
typedef  TYPE_1__ bot_state_t ;

/* Variables and functions */
 int /*<<< orphan*/  ClientName (int,char*,int) ; 
 int MAX_MESSAGE_SIZE ; 
 int /*<<< orphan*/  Q_stricmp (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * notleader ; 
 int /*<<< orphan*/  qtrue ; 

void BotVoiceChat_StopLeader(bot_state_t *bs, int client, int mode) {
	char netname[MAX_MESSAGE_SIZE];

	if (!Q_stricmp(bs->teamleader, ClientName(client, netname, sizeof(netname)))) {
		bs->teamleader[0] = '\0';
		notleader[client] = qtrue;
	}
}