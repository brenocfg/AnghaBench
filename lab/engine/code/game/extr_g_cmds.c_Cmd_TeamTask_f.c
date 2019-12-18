#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  userinfo ;
struct TYPE_4__ {int client; } ;
typedef  TYPE_1__ gentity_t ;
typedef  int /*<<< orphan*/  arg ;
struct TYPE_5__ {int clients; } ;

/* Variables and functions */
 int /*<<< orphan*/  ClientUserinfoChanged (int) ; 
 int /*<<< orphan*/  Info_SetValueForKey (char*,char*,int /*<<< orphan*/ ) ; 
 int MAX_INFO_STRING ; 
 int MAX_TOKEN_CHARS ; 
 int atoi (char*) ; 
 TYPE_2__ level ; 
 int trap_Argc () ; 
 int /*<<< orphan*/  trap_Argv (int,char*,int) ; 
 int /*<<< orphan*/  trap_GetUserinfo (int,char*,int) ; 
 int /*<<< orphan*/  trap_SetUserinfo (int,char*) ; 
 int /*<<< orphan*/  va (char*,int) ; 

void Cmd_TeamTask_f( gentity_t *ent ) {
	char userinfo[MAX_INFO_STRING];
	char		arg[MAX_TOKEN_CHARS];
	int task;
	int client = ent->client - level.clients;

	if ( trap_Argc() != 2 ) {
		return;
	}
	trap_Argv( 1, arg, sizeof( arg ) );
	task = atoi( arg );

	trap_GetUserinfo(client, userinfo, sizeof(userinfo));
	Info_SetValueForKey(userinfo, "teamtask", va("%d", task));
	trap_SetUserinfo(client, userinfo);
	ClientUserinfoChanged(client);
}