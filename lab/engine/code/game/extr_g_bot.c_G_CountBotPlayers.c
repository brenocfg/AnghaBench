#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int sessionTeam; } ;
struct TYPE_9__ {scalar_t__ connected; } ;
struct TYPE_11__ {TYPE_1__ sess; TYPE_2__ pers; } ;
typedef  TYPE_4__ gclient_t ;
struct TYPE_10__ {int svFlags; } ;
struct TYPE_14__ {TYPE_3__ r; } ;
struct TYPE_13__ {int integer; } ;
struct TYPE_12__ {TYPE_4__* clients; } ;

/* Variables and functions */
 scalar_t__ CON_DISCONNECTED ; 
 int SVF_BOT ; 
 TYPE_7__* g_entities ; 
 TYPE_6__ g_maxclients ; 
 TYPE_5__ level ; 

int G_CountBotPlayers( int team ) {
	int i, num;
	gclient_t	*cl;

	num = 0;
	for ( i=0 ; i< g_maxclients.integer ; i++ ) {
		cl = level.clients + i;
		if ( cl->pers.connected == CON_DISCONNECTED ) {
			continue;
		}
		if ( !(g_entities[i].r.svFlags & SVF_BOT) ) {
			continue;
		}
		if ( team >= 0 && cl->sess.sessionTeam != team ) {
			continue;
		}
		num++;
	}
	return num;
}