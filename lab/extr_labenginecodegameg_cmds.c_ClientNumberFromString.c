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
typedef  scalar_t__ qboolean ;
typedef  int /*<<< orphan*/  gentity_t ;
struct TYPE_4__ {scalar_t__ connected; int /*<<< orphan*/  netname; } ;
struct TYPE_5__ {TYPE_1__ pers; } ;
typedef  TYPE_2__ gclient_t ;
typedef  int /*<<< orphan*/  cleanName ;
struct TYPE_6__ {int maxclients; TYPE_2__* clients; } ;

/* Variables and functions */
 scalar_t__ CON_CONNECTED ; 
 int MAX_STRING_CHARS ; 
 int /*<<< orphan*/  Q_CleanStr (char*) ; 
 int /*<<< orphan*/  Q_stricmp (char*,char*) ; 
 int /*<<< orphan*/  Q_strncpyz (char*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ StringIsInteger (char*) ; 
 int atoi (char*) ; 
 int g_entities ; 
 TYPE_3__ level ; 
 int /*<<< orphan*/  trap_SendServerCommand (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  va (char*,char*) ; 

int ClientNumberFromString( gentity_t *to, char *s, qboolean checkNums, qboolean checkNames ) {
	gclient_t	*cl;
	int			idnum;
	char		cleanName[MAX_STRING_CHARS];

	if ( checkNums ) {
		// numeric values could be slot numbers
		if ( StringIsInteger( s ) ) {
			idnum = atoi( s );
			if ( idnum >= 0 && idnum < level.maxclients ) {
				cl = &level.clients[idnum];
				if ( cl->pers.connected == CON_CONNECTED ) {
					return idnum;
				}
			}
		}
	}

	if ( checkNames ) {
		// check for a name match
		for ( idnum=0,cl=level.clients ; idnum < level.maxclients ; idnum++,cl++ ) {
			if ( cl->pers.connected != CON_CONNECTED ) {
				continue;
			}
			Q_strncpyz(cleanName, cl->pers.netname, sizeof(cleanName));
			Q_CleanStr(cleanName);
			if ( !Q_stricmp( cleanName, s ) ) {
				return idnum;
			}
		}
	}

	trap_SendServerCommand( to-g_entities, va("print \"User %s is not on the server\n\"", s));
	return -1;
}