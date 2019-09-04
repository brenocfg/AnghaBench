#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vec3_t ;
typedef  int /*<<< orphan*/  gitem_t ;
struct TYPE_13__ {int /*<<< orphan*/  eType; } ;
struct TYPE_15__ {int count; TYPE_4__* client; int /*<<< orphan*/  health; int /*<<< orphan*/  pain_debounce_time; TYPE_1__ s; } ;
typedef  TYPE_3__ gentity_t ;
struct TYPE_14__ {int eventSequence; int* events; int* powerups; int /*<<< orphan*/ * stats; int /*<<< orphan*/  origin; } ;
struct TYPE_16__ {TYPE_2__ ps; } ;
typedef  TYPE_4__ gclient_t ;
struct TYPE_18__ {int integer; } ;
struct TYPE_17__ {int time; } ;

/* Variables and functions */
 int /*<<< orphan*/ * BG_FindItemForPowerup (size_t) ; 
 int DF_NO_FALLING ; 
 TYPE_3__* Drop_Item (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ET_PLAYER ; 
#define  EV_FALL_FAR 132 
#define  EV_FALL_MEDIUM 131 
#define  EV_FIRE_WEAPON 130 
#define  EV_USE_ITEM1 129 
#define  EV_USE_ITEM2 128 
 int /*<<< orphan*/  FireWeapon (TYPE_3__*) ; 
 int /*<<< orphan*/  G_Damage (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int MAX_PS_EVENTS ; 
 int /*<<< orphan*/  MOD_FALLING ; 
 size_t PW_BLUEFLAG ; 
 size_t PW_NEUTRALFLAG ; 
 size_t PW_REDFLAG ; 
 size_t STAT_MAX_HEALTH ; 
 int /*<<< orphan*/  SelectSpawnPoint (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TeleportPlayer (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_6__ g_dmflags ; 
 TYPE_5__ level ; 
 int /*<<< orphan*/  qfalse ; 

void ClientEvents( gentity_t *ent, int oldEventSequence ) {
	int		i, j;
	int		event;
	gclient_t *client;
	int		damage;
	vec3_t	origin, angles;
//	qboolean	fired;
	gitem_t *item;
	gentity_t *drop;

	client = ent->client;

	if ( oldEventSequence < client->ps.eventSequence - MAX_PS_EVENTS ) {
		oldEventSequence = client->ps.eventSequence - MAX_PS_EVENTS;
	}
	for ( i = oldEventSequence ; i < client->ps.eventSequence ; i++ ) {
		event = client->ps.events[ i & (MAX_PS_EVENTS-1) ];

		switch ( event ) {
		case EV_FALL_MEDIUM:
		case EV_FALL_FAR:
			if ( ent->s.eType != ET_PLAYER ) {
				break;		// not in the player model
			}
			if ( g_dmflags.integer & DF_NO_FALLING ) {
				break;
			}
			if ( event == EV_FALL_FAR ) {
				damage = 10;
			} else {
				damage = 5;
			}
			ent->pain_debounce_time = level.time + 200;	// no normal pain sound
			G_Damage (ent, NULL, NULL, NULL, NULL, damage, 0, MOD_FALLING);
			break;

		case EV_FIRE_WEAPON:
			FireWeapon( ent );
			break;

		case EV_USE_ITEM1:		// teleporter
			// drop flags in CTF
			item = NULL;
			j = 0;

			if ( ent->client->ps.powerups[ PW_REDFLAG ] ) {
				item = BG_FindItemForPowerup( PW_REDFLAG );
				j = PW_REDFLAG;
			} else if ( ent->client->ps.powerups[ PW_BLUEFLAG ] ) {
				item = BG_FindItemForPowerup( PW_BLUEFLAG );
				j = PW_BLUEFLAG;
			} else if ( ent->client->ps.powerups[ PW_NEUTRALFLAG ] ) {
				item = BG_FindItemForPowerup( PW_NEUTRALFLAG );
				j = PW_NEUTRALFLAG;
			}

			if ( item ) {
				drop = Drop_Item( ent, item, 0 );
				// decide how many seconds it has left
				drop->count = ( ent->client->ps.powerups[ j ] - level.time ) / 1000;
				if ( drop->count < 1 ) {
					drop->count = 1;
				}

				ent->client->ps.powerups[ j ] = 0;
			}

#ifdef MISSIONPACK
			if ( g_gametype.integer == GT_HARVESTER ) {
				if ( ent->client->ps.generic1 > 0 ) {
					if ( ent->client->sess.sessionTeam == TEAM_RED ) {
						item = BG_FindItem( "Blue Cube" );
					} else {
						item = BG_FindItem( "Red Cube" );
					}
					if ( item ) {
						for ( j = 0; j < ent->client->ps.generic1; j++ ) {
							drop = Drop_Item( ent, item, 0 );
							if ( ent->client->sess.sessionTeam == TEAM_RED ) {
								drop->spawnflags = TEAM_BLUE;
							} else {
								drop->spawnflags = TEAM_RED;
							}
						}
					}
					ent->client->ps.generic1 = 0;
				}
			}
#endif
			SelectSpawnPoint( ent->client->ps.origin, origin, angles, qfalse );
			TeleportPlayer( ent, origin, angles );
			break;

		case EV_USE_ITEM2:		// medkit
			ent->health = ent->client->ps.stats[STAT_MAX_HEALTH] + 25;

			break;

#ifdef MISSIONPACK
		case EV_USE_ITEM3:		// kamikaze
			// make sure the invulnerability is off
			ent->client->invulnerabilityTime = 0;
			// start the kamikze
			G_StartKamikaze( ent );
			break;

		case EV_USE_ITEM4:		// portal
			if( ent->client->portalID ) {
				DropPortalSource( ent );
			}
			else {
				DropPortalDestination( ent );
			}
			break;
		case EV_USE_ITEM5:		// invulnerability
			ent->client->invulnerabilityTime = level.time + 10000;
			break;
#endif

		default:
			break;
		}
	}

}