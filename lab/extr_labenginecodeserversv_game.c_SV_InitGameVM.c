#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  qboolean ;
struct TYPE_13__ {int /*<<< orphan*/  time; int /*<<< orphan*/  entityParsePoint; } ;
struct TYPE_12__ {int integer; } ;
struct TYPE_11__ {TYPE_2__* clients; } ;
struct TYPE_8__ {int (* make_random_seed ) (int /*<<< orphan*/ ) ;} ;
struct TYPE_10__ {int /*<<< orphan*/  userdata; TYPE_1__ hooks; } ;
struct TYPE_9__ {int /*<<< orphan*/ * gentity; } ;
typedef  TYPE_3__ DeepmindContext ;

/* Variables and functions */
 int /*<<< orphan*/  CM_EntityString () ; 
 int /*<<< orphan*/  GAME_INIT ; 
 int /*<<< orphan*/  VM_Call (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 TYPE_3__* dmlab_context () ; 
 int /*<<< orphan*/  gvm ; 
 int stub1 (int /*<<< orphan*/ ) ; 
 TYPE_6__ sv ; 
 TYPE_5__* sv_maxclients ; 
 TYPE_4__ svs ; 

__attribute__((used)) static void SV_InitGameVM( qboolean restart ) {
	int		i;
	DeepmindContext* ctx = dmlab_context();
	int seed = ctx->hooks.make_random_seed( ctx->userdata );

	// start the entity parsing at the beginning
	sv.entityParsePoint = CM_EntityString();

	// clear all gentity pointers that might still be set from
	// a previous level
	// https://zerowing.idsoftware.com/bugzilla/show_bug.cgi?id=522
	//   now done before GAME_INIT call
	for ( i = 0 ; i < sv_maxclients->integer ; i++ ) {
		svs.clients[i].gentity = NULL;
	}
	
	// use the current msec count for a random seed
	// init for this gamestate

	VM_Call (gvm, GAME_INIT, sv.time, seed, restart);
}