#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  origin; } ;
struct TYPE_7__ {int /*<<< orphan*/  absmin; } ;
struct TYPE_9__ {struct TYPE_9__* nextTrain; TYPE_2__ s; int /*<<< orphan*/  target; int /*<<< orphan*/  classname; TYPE_1__ r; } ;
typedef  TYPE_3__ gentity_t ;

/* Variables and functions */
 int /*<<< orphan*/  FOFS (int /*<<< orphan*/ ) ; 
 void* G_Find (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  G_Printf (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Reached_Train (TYPE_3__*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  targetname ; 
 int /*<<< orphan*/  vtos (int /*<<< orphan*/ ) ; 

void Think_SetupTrainTargets( gentity_t *ent ) {
	gentity_t		*path, *next, *start;

	ent->nextTrain = G_Find( NULL, FOFS(targetname), ent->target );
	if ( !ent->nextTrain ) {
		G_Printf( "func_train at %s with an unfound target\n",
			vtos(ent->r.absmin) );
		return;
	}

	start = NULL;
	for ( path = ent->nextTrain ; path != start ; path = next ) {
		if ( !start ) {
			start = path;
		}

		if ( !path->target ) {
			G_Printf( "Train corner at %s without a target\n",
				vtos(path->s.origin) );
			return;
		}

		// find a path_corner among the targets
		// there may also be other targets that get fired when the corner
		// is reached
		next = NULL;
		do {
			next = G_Find( next, FOFS(targetname), path->target );
			if ( !next ) {
				G_Printf( "Train corner at %s without a target path_corner\n",
					vtos(path->s.origin) );
				return;
			}
		} while ( strcmp( next->classname, "path_corner" ) );

		path->nextTrain = next;
	}

	// start the train moving from the first corner
	Reached_Train( ent );
}