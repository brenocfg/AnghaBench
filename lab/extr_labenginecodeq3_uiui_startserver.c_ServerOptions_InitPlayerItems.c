#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ curvalue; } ;
struct TYPE_12__ {scalar_t__ gametype; TYPE_5__* playerTeam; int /*<<< orphan*/ * playerNameBuffers; TYPE_3__* playerType; TYPE_1__ dedicated; scalar_t__ multiplayer; } ;
struct TYPE_10__ {int flags; } ;
struct TYPE_11__ {int curvalue; TYPE_4__ generic; } ;
struct TYPE_8__ {int flags; } ;
struct TYPE_9__ {int curvalue; TYPE_2__ generic; } ;

/* Variables and functions */
 scalar_t__ GT_TEAM ; 
 int PLAYER_SLOTS ; 
 int QMF_HIDDEN ; 
 int QMF_INACTIVE ; 
 int /*<<< orphan*/  Q_CleanStr (int /*<<< orphan*/ ) ; 
 TYPE_6__ s_serveroptions ; 
 int /*<<< orphan*/  trap_Cvar_VariableStringBuffer (char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void ServerOptions_InitPlayerItems( void ) {
	int		n;
	int		v;

	// init types
	if( s_serveroptions.multiplayer ) {
		v = 0;	// open
	}
	else {
		v = 1;	// bot
	}
	
	for( n = 0; n < PLAYER_SLOTS; n++ ) {
		s_serveroptions.playerType[n].curvalue = v;
	}

	if( s_serveroptions.multiplayer && (s_serveroptions.gametype < GT_TEAM) ) {
		for( n = 8; n < PLAYER_SLOTS; n++ ) {
			s_serveroptions.playerType[n].curvalue = 2;
		}
	}

	// if not a dedicated server, first slot is reserved for the human on the server
	if( s_serveroptions.dedicated.curvalue == 0 ) {
		// human
		s_serveroptions.playerType[0].generic.flags |= QMF_INACTIVE;
		s_serveroptions.playerType[0].curvalue = 0;
		trap_Cvar_VariableStringBuffer( "name", s_serveroptions.playerNameBuffers[0], sizeof(s_serveroptions.playerNameBuffers[0]) );
		Q_CleanStr( s_serveroptions.playerNameBuffers[0] );
	}

	// init teams
	if( s_serveroptions.gametype >= GT_TEAM ) {
		for( n = 0; n < (PLAYER_SLOTS / 2); n++ ) {
			s_serveroptions.playerTeam[n].curvalue = 0;
		}
		for( ; n < PLAYER_SLOTS; n++ ) {
			s_serveroptions.playerTeam[n].curvalue = 1;
		}
	}
	else {
		for( n = 0; n < PLAYER_SLOTS; n++ ) {
			s_serveroptions.playerTeam[n].generic.flags |= (QMF_INACTIVE|QMF_HIDDEN);
		}
	}
}