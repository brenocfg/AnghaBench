#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int lowAmmoWarning; TYPE_2__* snap; } ;
struct TYPE_8__ {int /*<<< orphan*/  noAmmoSound; } ;
struct TYPE_9__ {TYPE_3__ media; } ;
struct TYPE_6__ {int* stats; scalar_t__* ammo; } ;
struct TYPE_7__ {TYPE_1__ ps; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHAN_LOCAL_SOUND ; 
 size_t STAT_WEAPONS ; 
#define  WP_GRENADE_LAUNCHER 132 
 int WP_MACHINEGUN ; 
 int WP_NUM_WEAPONS ; 
#define  WP_PROX_LAUNCHER 131 
#define  WP_RAILGUN 130 
#define  WP_ROCKET_LAUNCHER 129 
#define  WP_SHOTGUN 128 
 TYPE_5__ cg ; 
 TYPE_4__ cgs ; 
 int /*<<< orphan*/  trap_S_StartLocalSound (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void CG_CheckAmmo( void ) {
	int		i;
	int		total;
	int		previous;
	int		weapons;

	// see about how many seconds of ammo we have remaining
	weapons = cg.snap->ps.stats[ STAT_WEAPONS ];
	total = 0;
	for ( i = WP_MACHINEGUN ; i < WP_NUM_WEAPONS ; i++ ) {
		if ( ! ( weapons & ( 1 << i ) ) ) {
			continue;
		}
		if ( cg.snap->ps.ammo[i] < 0 ) {
			continue;
		}
		switch ( i ) {
		case WP_ROCKET_LAUNCHER:
		case WP_GRENADE_LAUNCHER:
		case WP_RAILGUN:
		case WP_SHOTGUN:
#ifdef MISSIONPACK
		case WP_PROX_LAUNCHER:
#endif
			total += cg.snap->ps.ammo[i] * 1000;
			break;
		default:
			total += cg.snap->ps.ammo[i] * 200;
			break;
		}
		if ( total < 0 || total >= 5000 ) {
			cg.lowAmmoWarning = 0;
			return;
		}
	}

	previous = cg.lowAmmoWarning;

	if ( total == 0 ) {
		cg.lowAmmoWarning = 2;
	} else if ( total > 0 ) {
		cg.lowAmmoWarning = 1;
	}

	// play a sound on transitions
	if ( cg.lowAmmoWarning != previous ) {
		trap_S_StartLocalSound( cgs.media.noAmmoSound, CHAN_LOCAL_SOUND );
	}
}