#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_6__ ;
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  trace_t ;
typedef  int /*<<< orphan*/  trace ;
typedef  scalar_t__ qboolean ;
struct TYPE_21__ {int /*<<< orphan*/  classname; } ;
typedef  TYPE_5__ gitem_t ;
struct TYPE_20__ {int /*<<< orphan*/  origin; } ;
struct TYPE_19__ {int /*<<< orphan*/  currentOrigin; } ;
struct TYPE_22__ {int health; scalar_t__ inuse; int /*<<< orphan*/  classname; TYPE_4__ s; TYPE_3__ r; TYPE_2__* client; } ;
typedef  TYPE_6__ gentity_t ;
struct TYPE_17__ {int* stats; int* ammo; int /*<<< orphan*/ * persistant; } ;
struct TYPE_18__ {TYPE_1__ ps; } ;

/* Variables and functions */
 TYPE_5__* BG_FindItem (char*) ; 
 int /*<<< orphan*/  CheatsOk (TYPE_6__*) ; 
 char* ConcatArgs (int) ; 
 int /*<<< orphan*/  FinishSpawningItem (TYPE_6__*) ; 
 int /*<<< orphan*/  G_FreeEntity (TYPE_6__*) ; 
 TYPE_6__* G_Spawn () ; 
 int /*<<< orphan*/  G_SpawnItem (TYPE_6__*,TYPE_5__*) ; 
 int MAX_WEAPONS ; 
 size_t PERS_ASSIST_COUNT ; 
 size_t PERS_DEFEND_COUNT ; 
 size_t PERS_EXCELLENT_COUNT ; 
 size_t PERS_GAUNTLET_FRAG_COUNT ; 
 size_t PERS_IMPRESSIVE_COUNT ; 
 scalar_t__ Q_stricmp (char*,char*) ; 
 size_t STAT_ARMOR ; 
 size_t STAT_MAX_HEALTH ; 
 size_t STAT_WEAPONS ; 
 int /*<<< orphan*/  Touch_Item (TYPE_6__*,TYPE_6__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VectorCopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int WP_GRAPPLING_HOOK ; 
 int WP_NONE ; 
 int WP_NUM_WEAPONS ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ qfalse ; 
 scalar_t__ qtrue ; 

void Cmd_Give_f (gentity_t *ent)
{
	char		*name;
	gitem_t		*it;
	int			i;
	qboolean	give_all;
	gentity_t		*it_ent;
	trace_t		trace;

	if ( !CheatsOk( ent ) ) {
		return;
	}

	name = ConcatArgs( 1 );

	if (Q_stricmp(name, "all") == 0)
		give_all = qtrue;
	else
		give_all = qfalse;

	if (give_all || Q_stricmp( name, "health") == 0)
	{
		ent->health = ent->client->ps.stats[STAT_MAX_HEALTH];
		if (!give_all)
			return;
	}

	if (give_all || Q_stricmp(name, "weapons") == 0)
	{
		ent->client->ps.stats[STAT_WEAPONS] = (1 << WP_NUM_WEAPONS) - 1 - 
			( 1 << WP_GRAPPLING_HOOK ) - ( 1 << WP_NONE );
		if (!give_all)
			return;
	}

	if (give_all || Q_stricmp(name, "ammo") == 0)
	{
		for ( i = 0 ; i < MAX_WEAPONS ; i++ ) {
			ent->client->ps.ammo[i] = 999;
		}
		if (!give_all)
			return;
	}

	if (give_all || Q_stricmp(name, "armor") == 0)
	{
		ent->client->ps.stats[STAT_ARMOR] = 200;

		if (!give_all)
			return;
	}

	if (Q_stricmp(name, "excellent") == 0) {
		ent->client->ps.persistant[PERS_EXCELLENT_COUNT]++;
		return;
	}
	if (Q_stricmp(name, "impressive") == 0) {
		ent->client->ps.persistant[PERS_IMPRESSIVE_COUNT]++;
		return;
	}
	if (Q_stricmp(name, "gauntletaward") == 0) {
		ent->client->ps.persistant[PERS_GAUNTLET_FRAG_COUNT]++;
		return;
	}
	if (Q_stricmp(name, "defend") == 0) {
		ent->client->ps.persistant[PERS_DEFEND_COUNT]++;
		return;
	}
	if (Q_stricmp(name, "assist") == 0) {
		ent->client->ps.persistant[PERS_ASSIST_COUNT]++;
		return;
	}

	// spawn a specific item right on the player
	if ( !give_all ) {
		it = BG_FindItem (name);
		if (!it) {
			return;
		}

		it_ent = G_Spawn();
		VectorCopy( ent->r.currentOrigin, it_ent->s.origin );
		it_ent->classname = it->classname;
		G_SpawnItem (it_ent, it);
		FinishSpawningItem(it_ent );
		memset( &trace, 0, sizeof( trace ) );
		Touch_Item (it_ent, ent, &trace);
		if (it_ent->inuse) {
			G_FreeEntity( it_ent );
		}
	}
}