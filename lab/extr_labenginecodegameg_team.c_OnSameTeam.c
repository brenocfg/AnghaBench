#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  qboolean ;
struct TYPE_9__ {TYPE_2__* client; } ;
typedef  TYPE_3__ gentity_t ;
struct TYPE_10__ {scalar_t__ integer; } ;
struct TYPE_7__ {scalar_t__ sessionTeam; } ;
struct TYPE_8__ {TYPE_1__ sess; } ;

/* Variables and functions */
 scalar_t__ GT_TEAM ; 
 TYPE_4__ g_gametype ; 
 int /*<<< orphan*/  qfalse ; 
 int /*<<< orphan*/  qtrue ; 

qboolean OnSameTeam( gentity_t *ent1, gentity_t *ent2 ) {
	if ( !ent1->client || !ent2->client ) {
		return qfalse;
	}

	if ( g_gametype.integer < GT_TEAM ) {
		return qfalse;
	}

	if ( ent1->client->sess.sessionTeam == ent2->client->sess.sessionTeam ) {
		return qtrue;
	}

	return qfalse;
}