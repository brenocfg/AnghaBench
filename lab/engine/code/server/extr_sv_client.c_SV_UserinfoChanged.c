#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  remoteAddress; } ;
struct TYPE_9__ {char* userinfo; int rate; int snapshotMsec; int hasVoip; TYPE_1__ netchan; scalar_t__ compat; scalar_t__ lastSnapshotTime; int /*<<< orphan*/  name; } ;
typedef  TYPE_2__ client_t ;
struct TYPE_12__ {int integer; } ;
struct TYPE_11__ {int integer; } ;
struct TYPE_10__ {int integer; } ;

/* Variables and functions */
 int /*<<< orphan*/  Info_SetValueForKey (char*,char*,char*) ; 
 char* Info_ValueForKey (char*,char*) ; 
 int MAX_INFO_STRING ; 
 scalar_t__ NET_AdrToString (int /*<<< orphan*/ ) ; 
 scalar_t__ NET_IsLocalAddress (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Q_stricmp (char*,char*) ; 
 int /*<<< orphan*/  Q_strncpyz (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  SV_DropClient (TYPE_2__*,char*) ; 
 scalar_t__ Sys_IsLANAddress (int /*<<< orphan*/ ) ; 
 int atoi (char*) ; 
 TYPE_5__* com_dedicated ; 
 int qfalse ; 
 int strlen (char*) ; 
 TYPE_4__* sv_fps ; 
 TYPE_3__* sv_lanForceRate ; 

void SV_UserinfoChanged( client_t *cl ) {
	char	*val;
	char	*ip;
	int		i;
	int	len;

	// name for C code
	Q_strncpyz( cl->name, Info_ValueForKey (cl->userinfo, "name"), sizeof(cl->name) );

	// rate command

	// if the client is on the same subnet as the server and we aren't running an
	// internet public server, assume they don't need a rate choke
	if ( Sys_IsLANAddress( cl->netchan.remoteAddress ) && com_dedicated->integer != 2 && sv_lanForceRate->integer == 1) {
		cl->rate = 0;	// no rate limit
	} else {
		val = Info_ValueForKey (cl->userinfo, "rate");
		if (strlen(val)) {
			i = atoi(val);
			cl->rate = i;
			if (cl->rate < 1000) {
				cl->rate = 1000;
			} else if (cl->rate > 90000) {
				cl->rate = 90000;
			}
		} else {
			cl->rate = 3000;
		}
	}
	val = Info_ValueForKey (cl->userinfo, "handicap");
	if (strlen(val)) {
		i = atoi(val);
		if (i<=0 || i>100 || strlen(val) > 4) {
			Info_SetValueForKey( cl->userinfo, "handicap", "100" );
		}
	}

	// snaps command
	val = Info_ValueForKey (cl->userinfo, "snaps");
	
	if(strlen(val))
	{
		i = atoi(val);
		
		if(i < 1)
			i = 1;
		else if(i > sv_fps->integer)
			i = sv_fps->integer;

		i = 1000 / i;
	}
	else
		i = 50;

	if(i != cl->snapshotMsec)
	{
		// Reset last sent snapshot so we avoid desync between server frame time and snapshot send time
		cl->lastSnapshotTime = 0;
		cl->snapshotMsec = i;		
	}
	
#ifdef USE_VOIP
#ifdef LEGACY_PROTOCOL
	if(cl->compat)
		cl->hasVoip = qfalse;
	else
#endif
	{
		val = Info_ValueForKey(cl->userinfo, "cl_voipProtocol");
		cl->hasVoip = !Q_stricmp( val, "opus" );
	}
#endif

	// TTimo
	// maintain the IP information
	// the banning code relies on this being consistently present
	if( NET_IsLocalAddress(cl->netchan.remoteAddress) )
		ip = "localhost";
	else
		ip = (char*)NET_AdrToString( cl->netchan.remoteAddress );

	val = Info_ValueForKey( cl->userinfo, "ip" );
	if( val[0] )
		len = strlen( ip ) - strlen( val ) + strlen( cl->userinfo );
	else
		len = strlen( ip ) + 4 + strlen( cl->userinfo );

	if( len >= MAX_INFO_STRING )
		SV_DropClient( cl, "userinfo string length exceeded" );
	else
		Info_SetValueForKey( cl->userinfo, "ip", ip );

}