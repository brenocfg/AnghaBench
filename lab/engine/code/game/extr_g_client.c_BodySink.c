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
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int* trBase; } ;
struct TYPE_8__ {TYPE_1__ pos; } ;
struct TYPE_9__ {int timestamp; int nextthink; TYPE_2__ s; int /*<<< orphan*/  physicsObject; } ;
typedef  TYPE_3__ gentity_t ;
struct TYPE_10__ {int time; } ;

/* Variables and functions */
 TYPE_5__ level ; 
 int /*<<< orphan*/  qfalse ; 
 int /*<<< orphan*/  trap_UnlinkEntity (TYPE_3__*) ; 

void BodySink( gentity_t *ent ) {
	if ( level.time - ent->timestamp > 6500 ) {
		// the body ques are never actually freed, they are just unlinked
		trap_UnlinkEntity( ent );
		ent->physicsObject = qfalse;
		return;	
	}
	ent->nextthink = level.time + 100;
	ent->s.pos.trBase[2] -= 1;
}