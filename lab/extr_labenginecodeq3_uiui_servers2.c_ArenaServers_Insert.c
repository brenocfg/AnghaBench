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
struct TYPE_3__ {int pingtime; scalar_t__ nettype; int gametype; int /*<<< orphan*/  gamename; void* bPB; void* maxPing; void* minPing; void* maxclients; void* numclients; int /*<<< orphan*/  mapname; int /*<<< orphan*/  hostname; int /*<<< orphan*/  adrstr; } ;
typedef  TYPE_1__ servernode_t ;
struct TYPE_4__ {scalar_t__* numservers; scalar_t__ maxservers; TYPE_1__* serverlist; } ;

/* Variables and functions */
 int ARRAY_LEN (int /*<<< orphan*/ ) ; 
 int ArenaServers_MaxPing () ; 
 char* Info_ValueForKey (char*,char*) ; 
 int MAX_ADDRESSLENGTH ; 
 int MAX_HOSTNAMELENGTH ; 
 int MAX_MAPNAMELENGTH ; 
 int /*<<< orphan*/  Q_CleanStr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Q_strncpyz (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  Q_strupr (int /*<<< orphan*/ ) ; 
 scalar_t__ UIAS_FAVORITES ; 
 void* atoi (char*) ; 
 TYPE_2__ g_arenaservers ; 
 scalar_t__ g_servertype ; 
 char** gamenames ; 
 int /*<<< orphan*/  netnames ; 

__attribute__((used)) static void ArenaServers_Insert( char* adrstr, char* info, int pingtime )
{
	servernode_t*	servernodeptr;
	char*			s;
	int				i;


	if ((pingtime >= ArenaServers_MaxPing()) && (g_servertype != UIAS_FAVORITES))
	{
		// slow global or local servers do not get entered
		return;
	}

	if (*g_arenaservers.numservers >= g_arenaservers.maxservers) {
		// list full;
		servernodeptr = g_arenaservers.serverlist+(*g_arenaservers.numservers)-1;
	} else {
		// next slot
		servernodeptr = g_arenaservers.serverlist+(*g_arenaservers.numservers);
		(*g_arenaservers.numservers)++;
	}

	Q_strncpyz( servernodeptr->adrstr, adrstr, MAX_ADDRESSLENGTH );

	Q_strncpyz( servernodeptr->hostname, Info_ValueForKey( info, "hostname"), MAX_HOSTNAMELENGTH );
	Q_CleanStr( servernodeptr->hostname );
	Q_strupr( servernodeptr->hostname );

	Q_strncpyz( servernodeptr->mapname, Info_ValueForKey( info, "mapname"), MAX_MAPNAMELENGTH );
	Q_CleanStr( servernodeptr->mapname );
	Q_strupr( servernodeptr->mapname );

	servernodeptr->numclients = atoi( Info_ValueForKey( info, "clients") );
	servernodeptr->maxclients = atoi( Info_ValueForKey( info, "sv_maxclients") );
	servernodeptr->pingtime   = pingtime;
	servernodeptr->minPing    = atoi( Info_ValueForKey( info, "minPing") );
	servernodeptr->maxPing    = atoi( Info_ValueForKey( info, "maxPing") );
	servernodeptr->bPB = atoi( Info_ValueForKey( info, "punkbuster") );

	/*
	s = Info_ValueForKey( info, "nettype" );
	for (i=0; ;i++)
	{
		if (!netnames[i])
		{
			servernodeptr->nettype = 0;
			break;
		}
		else if (!Q_stricmp( netnames[i], s ))
		{
			servernodeptr->nettype = i;
			break;
		}
	}
	*/
	servernodeptr->nettype = atoi(Info_ValueForKey(info, "nettype"));
	if (servernodeptr->nettype < 0 || servernodeptr->nettype >= ARRAY_LEN(netnames) - 1) {
		servernodeptr->nettype = 0;
	}

	s = Info_ValueForKey( info, "game");
	i = atoi( Info_ValueForKey( info, "gametype") );
	if( i < 0 ) {
		i = 0;
	}
	else if( i > 11 ) {
		i = 12;
	}
	if( *s ) {
		servernodeptr->gametype = i;//-1;
		Q_strncpyz( servernodeptr->gamename, s, sizeof(servernodeptr->gamename) );
	}
	else {
		servernodeptr->gametype = i;
		Q_strncpyz( servernodeptr->gamename, gamenames[i], sizeof(servernodeptr->gamename) );
	}
}