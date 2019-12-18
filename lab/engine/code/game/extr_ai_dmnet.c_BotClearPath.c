#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int* vec3_t ;
struct TYPE_12__ {int* trBase; } ;
struct TYPE_14__ {scalar_t__ number; TYPE_1__ pos; } ;
typedef  TYPE_3__ entityState_t ;
struct TYPE_15__ {double fraction; scalar_t__ ent; } ;
typedef  TYPE_4__ bsp_trace_t ;
struct TYPE_13__ {int weapon; } ;
struct TYPE_16__ {scalar_t__ blockedbyavoidspot_time; int numproxmines; scalar_t__* inventory; int /*<<< orphan*/  client; int /*<<< orphan*/  entitynum; int /*<<< orphan*/  eye; int /*<<< orphan*/  viewangles; TYPE_2__ cur_ps; scalar_t__* proxmines; int /*<<< orphan*/  origin; scalar_t__ kamikazebody; } ;
typedef  TYPE_5__ bot_state_t ;
struct TYPE_17__ {int flags; int weapon; int /*<<< orphan*/  ideal_viewangles; } ;
typedef  TYPE_6__ bot_moveresult_t ;

/* Variables and functions */
 int /*<<< orphan*/  BotAI_GetEntityState (scalar_t__,TYPE_3__*) ; 
 int /*<<< orphan*/  BotAI_Trace (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int BotSelectActivateWeapon (TYPE_5__*) ; 
 scalar_t__ FloatTime () ; 
 size_t INVENTORY_BFG10K ; 
 size_t INVENTORY_BFGAMMO ; 
 size_t INVENTORY_CELLS ; 
 size_t INVENTORY_PLASMAGUN ; 
 size_t INVENTORY_ROCKETLAUNCHER ; 
 size_t INVENTORY_ROCKETS ; 
 scalar_t__ InFieldOfVision (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MASK_SHOT ; 
 int MOVERESULT_BLOCKEDBYAVOIDSPOT ; 
 int MOVERESULT_MOVEMENTVIEW ; 
 int MOVERESULT_MOVEMENTWEAPON ; 
 int /*<<< orphan*/  VectorCopy (int*,int*) ; 
 float VectorLength (int*) ; 
 int /*<<< orphan*/  VectorSubtract (int*,int /*<<< orphan*/ ,int*) ; 
 int WEAPONINDEX_BFG ; 
 int WEAPONINDEX_PLASMAGUN ; 
 int WEAPONINDEX_ROCKET_LAUNCHER ; 
 int /*<<< orphan*/  trap_EA_Attack (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vectoangles (int*,int /*<<< orphan*/ ) ; 

void BotClearPath(bot_state_t *bs, bot_moveresult_t *moveresult) {
	int i, bestmine;
	float dist, bestdist;
	vec3_t target, dir;
	bsp_trace_t bsptrace;
	entityState_t state;

	// if there is a dead body wearing kamikze nearby
	if (bs->kamikazebody) {
		// if the bot's view angles and weapon are not used for movement
		if ( !(moveresult->flags & (MOVERESULT_MOVEMENTVIEW | MOVERESULT_MOVEMENTWEAPON)) ) {
			//
			BotAI_GetEntityState(bs->kamikazebody, &state);
			VectorCopy(state.pos.trBase, target);
			target[2] += 8;
			VectorSubtract(target, bs->eye, dir);
			vectoangles(dir, moveresult->ideal_viewangles);
			//
			moveresult->weapon = BotSelectActivateWeapon(bs);
			if (moveresult->weapon == -1) {
				// FIXME: run away!
				moveresult->weapon = 0;
			}
			if (moveresult->weapon) {
				//
				moveresult->flags |= MOVERESULT_MOVEMENTWEAPON | MOVERESULT_MOVEMENTVIEW;
				// if holding the right weapon
				if (bs->cur_ps.weapon == moveresult->weapon) {
					// if the bot is pretty close with its aim
					if (InFieldOfVision(bs->viewangles, 20, moveresult->ideal_viewangles)) {
						//
						BotAI_Trace(&bsptrace, bs->eye, NULL, NULL, target, bs->entitynum, MASK_SHOT);
						// if the mine is visible from the current position
						if (bsptrace.fraction >= 1.0 || bsptrace.ent == state.number) {
							// shoot at the mine
							trap_EA_Attack(bs->client);
						}
					}
				}
			}
		}
	}
	if (moveresult->flags & MOVERESULT_BLOCKEDBYAVOIDSPOT) {
		bs->blockedbyavoidspot_time = FloatTime() + 5;
	}
	// if blocked by an avoid spot and the view angles and weapon are used for movement
	if (bs->blockedbyavoidspot_time > FloatTime() &&
		!(moveresult->flags & (MOVERESULT_MOVEMENTVIEW | MOVERESULT_MOVEMENTWEAPON)) ) {
		bestdist = 300;
		bestmine = -1;
		for (i = 0; i < bs->numproxmines; i++) {
			BotAI_GetEntityState(bs->proxmines[i], &state);
			VectorSubtract(state.pos.trBase, bs->origin, dir);
			dist = VectorLength(dir);
			if (dist < bestdist) {
				bestdist = dist;
				bestmine = i;
			}
		}
		if (bestmine != -1) {
			//
			// state->generic1 == TEAM_RED || state->generic1 == TEAM_BLUE
			//
			// deactivate prox mines in the bot's path by shooting
			// rockets or plasma cells etc. at them
			BotAI_GetEntityState(bs->proxmines[bestmine], &state);
			VectorCopy(state.pos.trBase, target);
			target[2] += 2;
			VectorSubtract(target, bs->eye, dir);
			vectoangles(dir, moveresult->ideal_viewangles);
			// if the bot has a weapon that does splash damage
			if (bs->inventory[INVENTORY_PLASMAGUN] > 0 && bs->inventory[INVENTORY_CELLS] > 0)
				moveresult->weapon = WEAPONINDEX_PLASMAGUN;
			else if (bs->inventory[INVENTORY_ROCKETLAUNCHER] > 0 && bs->inventory[INVENTORY_ROCKETS] > 0)
				moveresult->weapon = WEAPONINDEX_ROCKET_LAUNCHER;
			else if (bs->inventory[INVENTORY_BFG10K] > 0 && bs->inventory[INVENTORY_BFGAMMO] > 0)
				moveresult->weapon = WEAPONINDEX_BFG;
			else {
				moveresult->weapon = 0;
			}
			if (moveresult->weapon) {
				//
				moveresult->flags |= MOVERESULT_MOVEMENTWEAPON | MOVERESULT_MOVEMENTVIEW;
				// if holding the right weapon
				if (bs->cur_ps.weapon == moveresult->weapon) {
					// if the bot is pretty close with its aim
					if (InFieldOfVision(bs->viewangles, 20, moveresult->ideal_viewangles)) {
						//
						BotAI_Trace(&bsptrace, bs->eye, NULL, NULL, target, bs->entitynum, MASK_SHOT);
						// if the mine is visible from the current position
						if (bsptrace.fraction >= 1.0 || bsptrace.ent == state.number) {
							// shoot at the mine
							trap_EA_Attack(bs->client);
						}
					}
				}
			}
		}
	}
}