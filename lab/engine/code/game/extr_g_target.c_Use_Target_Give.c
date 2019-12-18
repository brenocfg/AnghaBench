#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  trace_t ;
typedef  int /*<<< orphan*/  trace ;
struct TYPE_10__ {scalar_t__ nextthink; int /*<<< orphan*/  item; int /*<<< orphan*/  target; int /*<<< orphan*/  client; } ;
typedef  TYPE_1__ gentity_t ;

/* Variables and functions */
 int /*<<< orphan*/  FOFS (int /*<<< orphan*/ ) ; 
 TYPE_1__* G_Find (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Touch_Item (TYPE_1__*,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  targetname ; 
 int /*<<< orphan*/  trap_UnlinkEntity (TYPE_1__*) ; 

void Use_Target_Give( gentity_t *ent, gentity_t *other, gentity_t *activator ) {
	gentity_t	*t;
	trace_t		trace;

	if ( !activator->client ) {
		return;
	}

	if ( !ent->target ) {
		return;
	}

	memset( &trace, 0, sizeof( trace ) );
	t = NULL;
	while ( (t = G_Find (t, FOFS(targetname), ent->target)) != NULL ) {
		if ( !t->item ) {
			continue;
		}
		Touch_Item( t, activator, &trace );

		// make sure it isn't going to respawn or show any events
		t->nextthink = 0;
		trap_UnlinkEntity( t );
	}
}