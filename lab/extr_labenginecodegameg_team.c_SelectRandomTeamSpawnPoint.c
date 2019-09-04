#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ team_t ;
typedef  scalar_t__ qboolean ;
struct TYPE_6__ {int flags; } ;
typedef  TYPE_1__ gentity_t ;

/* Variables and functions */
 int FL_NO_BOTS ; 
 int FL_NO_HUMANS ; 
 int /*<<< orphan*/  FOFS (char*) ; 
 TYPE_1__* G_Find (TYPE_1__*,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ SpotWouldTelefrag (TYPE_1__*) ; 
 int TEAM_BEGIN ; 
 scalar_t__ TEAM_BLUE ; 
 scalar_t__ TEAM_RED ; 
 float random () ; 

gentity_t *SelectRandomTeamSpawnPoint( int teamstate, team_t team, qboolean isbot) {
	gentity_t *spot = NULL;
	gentity_t *best_spot = NULL;
	float spot_count = 0;

	char		*classname;

	if (teamstate == TEAM_BEGIN) {
		if (team == TEAM_RED)
			classname = "team_CTF_redplayer";
		else if (team == TEAM_BLUE)
			classname = "team_CTF_blueplayer";
		else
			return NULL;
	} else {
		if (team == TEAM_RED)
			classname = "team_CTF_redspawn";
		else if (team == TEAM_BLUE)
			classname = "team_CTF_bluespawn";
		else
			return NULL;
	}

	while ( ( spot = G_Find( spot, FOFS(classname), classname ) ) != NULL ) {
		if ( ( (spot->flags & FL_NO_BOTS) && isbot) || ((spot->flags & FL_NO_HUMANS) && !isbot) )
			continue;

		if ( SpotWouldTelefrag( spot ) ) {
			// Ensure we have one good spot, in case they're all telefrag spots.
			if ( best_spot == NULL ) {
				best_spot = spot;
			}
			continue;
		}

		spot_count += 1.0f;
		if ( random() * spot_count <= 1.0f ) {
			best_spot = spot;
		}
	}

	return best_spot;
}