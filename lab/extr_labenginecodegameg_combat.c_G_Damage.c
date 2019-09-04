#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_38__   TYPE_5__ ;
typedef  struct TYPE_37__   TYPE_4__ ;
typedef  struct TYPE_36__   TYPE_3__ ;
typedef  struct TYPE_35__   TYPE_2__ ;
typedef  struct TYPE_34__   TYPE_1__ ;
typedef  struct TYPE_33__   TYPE_19__ ;
typedef  struct TYPE_32__   TYPE_17__ ;
typedef  struct TYPE_31__   TYPE_16__ ;
typedef  struct TYPE_30__   TYPE_15__ ;
typedef  struct TYPE_29__   TYPE_14__ ;

/* Type definitions */
typedef  scalar_t__ vec3_t ;
struct TYPE_36__ {scalar_t__ eType; size_t number; } ;
struct TYPE_34__ {scalar_t__ currentOrigin; } ;
struct TYPE_37__ {scalar_t__ moverState; int flags; int health; int /*<<< orphan*/  (* pain ) (TYPE_4__*,TYPE_4__*,int) ;int /*<<< orphan*/  (* die ) (TYPE_4__*,TYPE_4__*,TYPE_4__*,int,int) ;struct TYPE_37__* enemy; TYPE_5__* client; TYPE_3__ s; TYPE_1__ r; int /*<<< orphan*/  (* use ) (TYPE_4__*,TYPE_4__*,TYPE_4__*) ;int /*<<< orphan*/  takedamage; } ;
typedef  TYPE_4__ gentity_t ;
struct TYPE_35__ {int* stats; int pm_time; size_t* persistant; scalar_t__* powerups; int /*<<< orphan*/  pm_flags; int /*<<< orphan*/  velocity; } ;
struct TYPE_38__ {int damage_armor; int damage_blood; int damage_knockback; size_t lasthurt_client; int lasthurt_mod; TYPE_2__ ps; int /*<<< orphan*/  damage_fromWorld; int /*<<< orphan*/  damage_from; scalar_t__ noclip; } ;
typedef  TYPE_5__ gclient_t ;
struct TYPE_33__ {scalar_t__ integer; } ;
struct TYPE_32__ {int /*<<< orphan*/  integer; } ;
struct TYPE_31__ {scalar_t__ integer; } ;
struct TYPE_30__ {float value; } ;
struct TYPE_29__ {int /*<<< orphan*/  time; scalar_t__ intermissionQueued; } ;

/* Variables and functions */
 int CheckArmor (TYPE_4__*,int,int) ; 
 int DAMAGE_NO_KNOCKBACK ; 
 int DAMAGE_NO_PROTECTION ; 
 int DAMAGE_RADIUS ; 
 size_t ENTITYNUM_WORLD ; 
 scalar_t__ ET_GENERAL ; 
 scalar_t__ ET_MISSILE ; 
 scalar_t__ ET_MOVER ; 
 int /*<<< orphan*/  EV_POWERUP_BATTLESUIT ; 
 int FL_GODMODE ; 
 int FL_NO_KNOCKBACK ; 
 scalar_t__ GT_CTF ; 
 int /*<<< orphan*/  G_AddEvent (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  G_Printf (char*,int /*<<< orphan*/ ,size_t,int,int,int) ; 
 int MOD_FALLING ; 
 scalar_t__ MOVER_POS1 ; 
 scalar_t__ OnSameTeam (TYPE_4__*,TYPE_4__*) ; 
 size_t PERS_ATTACKEE_ARMOR ; 
 size_t PERS_ATTACKER ; 
 size_t PERS_HITS ; 
 int /*<<< orphan*/  PMF_TIME_KNOCKBACK ; 
 size_t PW_BATTLESUIT ; 
 size_t STAT_ARMOR ; 
 size_t STAT_HEALTH ; 
 size_t STAT_MAX_HEALTH ; 
 int /*<<< orphan*/  Team_CheckHurtCarrier (TYPE_4__*,TYPE_4__*) ; 
 int /*<<< orphan*/  VectorAdd (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VectorCopy (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VectorNormalize (scalar_t__) ; 
 int /*<<< orphan*/  VectorScale (scalar_t__,float,scalar_t__) ; 
 TYPE_19__ g_debugDamage ; 
 TYPE_4__* g_entities ; 
 TYPE_17__ g_friendlyFire ; 
 TYPE_16__ g_gametype ; 
 TYPE_15__ g_knockback ; 
 TYPE_14__ level ; 
 int /*<<< orphan*/  qfalse ; 
 int /*<<< orphan*/  qtrue ; 
 int /*<<< orphan*/  stub1 (TYPE_4__*,TYPE_4__*,TYPE_4__*) ; 
 int /*<<< orphan*/  stub2 (TYPE_4__*,TYPE_4__*,TYPE_4__*,int,int) ; 
 int /*<<< orphan*/  stub3 (TYPE_4__*,TYPE_4__*,int) ; 

void G_Damage( gentity_t *targ, gentity_t *inflictor, gentity_t *attacker,
			   vec3_t dir, vec3_t point, int damage, int dflags, int mod ) {
	gclient_t	*client;
	int			take;
	int			asave;
	int			knockback;
	int			max;
#ifdef MISSIONPACK
	vec3_t		bouncedir, impactpoint;
#endif

	if (!targ->takedamage) {
		return;
	}

	// the intermission has already been qualified for, so don't
	// allow any extra scoring
	if ( level.intermissionQueued ) {
		return;
	}
#ifdef MISSIONPACK
	if ( targ->client && mod != MOD_JUICED) {
		if ( targ->client->invulnerabilityTime > level.time) {
			if ( dir && point ) {
				G_InvulnerabilityEffect( targ, dir, point, impactpoint, bouncedir );
			}
			return;
		}
	}
#endif
	if ( !inflictor ) {
		inflictor = &g_entities[ENTITYNUM_WORLD];
	}
	if ( !attacker ) {
		attacker = &g_entities[ENTITYNUM_WORLD];
	}

	// shootable doors / buttons don't actually have any health
	if ( targ->s.eType == ET_MOVER ) {
		if ( targ->use && targ->moverState == MOVER_POS1 ) {
			targ->use( targ, inflictor, attacker );
		}
		return;
	}
#ifdef MISSIONPACK
	if( g_gametype.integer == GT_OBELISK && CheckObeliskAttack( targ, attacker ) ) {
		return;
	}
#endif
	// reduce damage by the attacker's handicap value
	// unless they are rocket jumping
	if ( attacker->client && attacker != targ ) {
		max = attacker->client->ps.stats[STAT_MAX_HEALTH];
#ifdef MISSIONPACK
		if( bg_itemlist[attacker->client->ps.stats[STAT_PERSISTANT_POWERUP]].giTag == PW_GUARD ) {
			max /= 2;
		}
#endif
		damage = damage * max / 100;
	}

	client = targ->client;

	if ( client ) {
		if ( client->noclip ) {
			return;
		}
	}

	if ( !dir ) {
		dflags |= DAMAGE_NO_KNOCKBACK;
	} else {
		VectorNormalize(dir);
	}

	knockback = damage;
	if ( knockback > 200 ) {
		knockback = 200;
	}
	if ( targ->flags & FL_NO_KNOCKBACK ) {
		knockback = 0;
	}
	if ( dflags & DAMAGE_NO_KNOCKBACK ) {
		knockback = 0;
	}

	// figure momentum add, even if the damage won't be taken
	if ( knockback && targ->client ) {
		vec3_t	kvel;
		float	mass;

		mass = 200;

		VectorScale (dir, g_knockback.value * (float)knockback / mass, kvel);
		VectorAdd (targ->client->ps.velocity, kvel, targ->client->ps.velocity);

		// set the timer so that the other client can't cancel
		// out the movement immediately
		if ( !targ->client->ps.pm_time ) {
			int		t;

			t = knockback * 2;
			if ( t < 50 ) {
				t = 50;
			}
			if ( t > 200 ) {
				t = 200;
			}
			targ->client->ps.pm_time = t;
			targ->client->ps.pm_flags |= PMF_TIME_KNOCKBACK;
		}
	}

	// check for completely getting out of the damage
	if ( !(dflags & DAMAGE_NO_PROTECTION) ) {

		// if TF_NO_FRIENDLY_FIRE is set, don't do damage to the target
		// if the attacker was on the same team
#ifdef MISSIONPACK
		if ( mod != MOD_JUICED && targ != attacker && !(dflags & DAMAGE_NO_TEAM_PROTECTION) && OnSameTeam (targ, attacker)  ) {
#else	
		if ( targ != attacker && OnSameTeam (targ, attacker)  ) {
#endif
			if ( !g_friendlyFire.integer ) {
				return;
			}
		}
#ifdef MISSIONPACK
		if (mod == MOD_PROXIMITY_MINE) {
			if (inflictor && inflictor->parent && OnSameTeam(targ, inflictor->parent)) {
				return;
			}
			if (targ == attacker) {
				return;
			}
		}
#endif

		// check for godmode
		if ( targ->flags & FL_GODMODE ) {
			return;
		}
	}

	// battlesuit protects from all radius damage (but takes knockback)
	// and protects 50% against all damage
	if ( client && client->ps.powerups[PW_BATTLESUIT] ) {
		G_AddEvent( targ, EV_POWERUP_BATTLESUIT, 0 );
		if ( ( dflags & DAMAGE_RADIUS ) || ( mod == MOD_FALLING ) ) {
			return;
		}
		damage *= 0.5;
	}

	// add to the attacker's hit counter (if the target isn't a general entity like a prox mine)
	if ( attacker->client && client
			&& targ != attacker && targ->health > 0
			&& targ->s.eType != ET_MISSILE
			&& targ->s.eType != ET_GENERAL) {
		if ( OnSameTeam( targ, attacker ) ) {
			attacker->client->ps.persistant[PERS_HITS]--;
		} else {
			attacker->client->ps.persistant[PERS_HITS]++;
		}
		attacker->client->ps.persistant[PERS_ATTACKEE_ARMOR] = (targ->health<<8)|(client->ps.stats[STAT_ARMOR]);
	}

	// always give half damage if hurting self
	// calculated after knockback, so rocket jumping works
	if ( targ == attacker) {
		damage *= 0.5;
	}

	if ( damage < 1 ) {
		damage = 1;
	}
	take = damage;

	// save some from armor
	asave = CheckArmor (targ, take, dflags);
	take -= asave;

	if ( g_debugDamage.integer ) {
		G_Printf( "%i: client:%i health:%i damage:%i armor:%i\n", level.time, targ->s.number,
			targ->health, take, asave );
	}

	// add to the damage inflicted on a player this frame
	// the total will be turned into screen blends and view angle kicks
	// at the end of the frame
	if ( client ) {
		if ( attacker ) {
			client->ps.persistant[PERS_ATTACKER] = attacker->s.number;
		} else {
			client->ps.persistant[PERS_ATTACKER] = ENTITYNUM_WORLD;
		}
		client->damage_armor += asave;
		client->damage_blood += take;
		client->damage_knockback += knockback;
		if ( dir ) {
			VectorCopy ( dir, client->damage_from );
			client->damage_fromWorld = qfalse;
		} else {
			VectorCopy ( targ->r.currentOrigin, client->damage_from );
			client->damage_fromWorld = qtrue;
		}
	}

	// See if it's the player hurting the emeny flag carrier
#ifdef MISSIONPACK
	if( g_gametype.integer == GT_CTF || g_gametype.integer == GT_1FCTF ) {
#else	
	if( g_gametype.integer == GT_CTF) {
#endif
		Team_CheckHurtCarrier(targ, attacker);
	}

	if (targ->client) {
		// set the last client who damaged the target
		targ->client->lasthurt_client = attacker->s.number;
		targ->client->lasthurt_mod = mod;
	}

	// do the damage
	if (take) {
		targ->health = targ->health - take;
		if ( targ->client ) {
			targ->client->ps.stats[STAT_HEALTH] = targ->health;
		}
			
		if ( targ->health <= 0 ) {
			if ( client )
				targ->flags |= FL_NO_KNOCKBACK;

			if (targ->health < -999)
				targ->health = -999;

			targ->enemy = attacker;
			targ->die (targ, inflictor, attacker, take, mod);
			return;
		} else if ( targ->pain ) {
			targ->pain (targ, attacker, take);
		}
	}

}