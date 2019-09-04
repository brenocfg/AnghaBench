#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  masterstr ;
typedef  int /*<<< orphan*/  cvarname ;
struct TYPE_7__ {int /*<<< orphan*/  string; } ;
struct TYPE_5__ {int flags; } ;
struct TYPE_6__ {TYPE_1__ generic; } ;
struct TYPE_8__ {TYPE_3__ status; scalar_t__* numservers; scalar_t__ numqueriedservers; scalar_t__ currentping; int /*<<< orphan*/  maxservers; int /*<<< orphan*/  serverlist; TYPE_2__ remove; } ;

/* Variables and functions */
 int /*<<< orphan*/  ArenaServers_StartRefresh () ; 
 int /*<<< orphan*/  ArenaServers_StopRefresh () ; 
 int /*<<< orphan*/  ArenaServers_UpdateMenu () ; 
 int /*<<< orphan*/  Com_sprintf (char*,int,char*,int) ; 
 int /*<<< orphan*/  MAX_FAVORITESERVERS ; 
 int /*<<< orphan*/  MAX_GLOBALSERVERS ; 
 int /*<<< orphan*/  MAX_LOCALSERVERS ; 
 int QMF_HIDDEN ; 
 int QMF_INACTIVE ; 
#define  UIAS_FAVORITES 135 
#define  UIAS_GLOBAL0 134 
#define  UIAS_GLOBAL1 133 
#define  UIAS_GLOBAL2 132 
#define  UIAS_GLOBAL3 131 
#define  UIAS_GLOBAL4 130 
#define  UIAS_GLOBAL5 129 
#define  UIAS_LOCAL 128 
 int UIAS_NUM_SOURCES ; 
 TYPE_4__ g_arenaservers ; 
 int /*<<< orphan*/  g_favoriteserverlist ; 
 int /*<<< orphan*/ * g_globalserverlist ; 
 int /*<<< orphan*/  g_localserverlist ; 
 scalar_t__ g_numfavoriteservers ; 
 scalar_t__* g_numglobalservers ; 
 scalar_t__ g_numlocalservers ; 
 int g_servertype ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  trap_Cvar_VariableStringBuffer (char*,char*,int) ; 

int ArenaServers_SetType( int type )
{
	ArenaServers_StopRefresh();

	if(type >= UIAS_GLOBAL1 && type <= UIAS_GLOBAL5)
	{
		char masterstr[2], cvarname[sizeof("sv_master1")];
		int direction;
		
		if (type == g_servertype || type == ((g_servertype+1) % UIAS_NUM_SOURCES)) {
			direction = 1;
		} else {
			direction = -1;
		}

		while(type >= UIAS_GLOBAL1 && type <= UIAS_GLOBAL5)
		{
			Com_sprintf(cvarname, sizeof(cvarname), "sv_master%d", type - UIAS_GLOBAL0);
			trap_Cvar_VariableStringBuffer(cvarname, masterstr, sizeof(masterstr));
			if(*masterstr)
				break;
			
			type += direction;
		}
	}

	g_servertype = type;

	switch( type ) {
	default:
	case UIAS_LOCAL:
		g_arenaservers.remove.generic.flags |= (QMF_INACTIVE|QMF_HIDDEN);
		g_arenaservers.serverlist = g_localserverlist;
		g_arenaservers.numservers = &g_numlocalservers;
		g_arenaservers.maxservers = MAX_LOCALSERVERS;
		break;

	case UIAS_GLOBAL0:
	case UIAS_GLOBAL1:
	case UIAS_GLOBAL2:
	case UIAS_GLOBAL3:
	case UIAS_GLOBAL4:
	case UIAS_GLOBAL5:
		g_arenaservers.remove.generic.flags |= (QMF_INACTIVE|QMF_HIDDEN);
		g_arenaservers.serverlist = g_globalserverlist[type-UIAS_GLOBAL0];
		g_arenaservers.numservers = &g_numglobalservers[type-UIAS_GLOBAL0];
		g_arenaservers.maxservers = MAX_GLOBALSERVERS;
		break;

	case UIAS_FAVORITES:
		g_arenaservers.remove.generic.flags &= ~(QMF_INACTIVE|QMF_HIDDEN);
		g_arenaservers.serverlist = g_favoriteserverlist;
		g_arenaservers.numservers = &g_numfavoriteservers;
		g_arenaservers.maxservers = MAX_FAVORITESERVERS;
		break;

	}

	if( !*g_arenaservers.numservers ) {
		ArenaServers_StartRefresh();
	}
	else {
		// avoid slow operation, use existing results
		g_arenaservers.currentping       = *g_arenaservers.numservers;
		g_arenaservers.numqueriedservers = *g_arenaservers.numservers; 
		ArenaServers_UpdateMenu();
		strcpy(g_arenaservers.status.string,"hit refresh to update");
	}
	
	return type;
}