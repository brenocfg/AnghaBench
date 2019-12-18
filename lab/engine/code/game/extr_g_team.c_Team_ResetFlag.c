#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int flags; } ;
typedef  TYPE_1__ gentity_t ;

/* Variables and functions */
 int /*<<< orphan*/  FLAG_ATBASE ; 
 int FL_DROPPED_ITEM ; 
 int /*<<< orphan*/  FOFS (int /*<<< orphan*/ ) ; 
 TYPE_1__* G_Find (TYPE_1__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  G_FreeEntity (TYPE_1__*) ; 
 int /*<<< orphan*/  RespawnItem (TYPE_1__*) ; 
#define  TEAM_BLUE 130 
#define  TEAM_FREE 129 
#define  TEAM_RED 128 
 int /*<<< orphan*/  Team_SetFlagStatus (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  classname ; 

gentity_t *Team_ResetFlag( int team ) {
	char *c;
	gentity_t *ent, *rent = NULL;

	switch (team) {
	case TEAM_RED:
		c = "team_CTF_redflag";
		break;
	case TEAM_BLUE:
		c = "team_CTF_blueflag";
		break;
	case TEAM_FREE:
		c = "team_CTF_neutralflag";
		break;
	default:
		return NULL;
	}

	ent = NULL;
	while ((ent = G_Find (ent, FOFS(classname), c)) != NULL) {
		if (ent->flags & FL_DROPPED_ITEM)
			G_FreeEntity(ent);
		else {
			rent = ent;
			RespawnItem(ent);
		}
	}

	Team_SetFlagStatus( team, FLAG_ATBASE );

	return rent;
}