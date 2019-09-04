#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  trBase; } ;
struct TYPE_9__ {int frame; int clientNum; TYPE_2__ pos; int /*<<< orphan*/  origin; int /*<<< orphan*/  loopSound; int /*<<< orphan*/  eventParm; int /*<<< orphan*/  eType; } ;
struct TYPE_7__ {int /*<<< orphan*/  svFlags; } ;
struct TYPE_10__ {int wait; int random; int spawnflags; TYPE_3__ s; TYPE_1__ r; int /*<<< orphan*/  use; int /*<<< orphan*/  noise_index; } ;
typedef  TYPE_4__ gentity_t ;
typedef  int /*<<< orphan*/  buffer ;

/* Variables and functions */
 int /*<<< orphan*/  Com_sprintf (char*,int,char*,char*) ; 
 int /*<<< orphan*/  ET_SPEAKER ; 
 int /*<<< orphan*/  G_Error (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  G_SoundIndex (char*) ; 
 int /*<<< orphan*/  G_SpawnFloat (char*,char*,int*) ; 
 int /*<<< orphan*/  G_SpawnString (char*,char*,char**) ; 
 int MAX_QPATH ; 
 int /*<<< orphan*/  Q_strncpyz (char*,char*,int) ; 
 int /*<<< orphan*/  SVF_BROADCAST ; 
 int /*<<< orphan*/  Use_Target_Speaker ; 
 int /*<<< orphan*/  VectorCopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strstr (char*,char*) ; 
 int /*<<< orphan*/  trap_LinkEntity (TYPE_4__*) ; 
 int /*<<< orphan*/  vtos (int /*<<< orphan*/ ) ; 

void SP_target_speaker( gentity_t *ent ) {
	char	buffer[MAX_QPATH];
	char	*s;

	G_SpawnFloat( "wait", "0", &ent->wait );
	G_SpawnFloat( "random", "0", &ent->random );

	if ( !G_SpawnString( "noise", "NOSOUND", &s ) ) {
		G_Error( "target_speaker without a noise key at %s", vtos( ent->s.origin ) );
	}

	// force all client relative sounds to be "activator" speakers that
	// play on the entity that activates it
	if ( s[0] == '*' ) {
		ent->spawnflags |= 8;
	}

	if (!strstr( s, ".wav" )) {
		Com_sprintf (buffer, sizeof(buffer), "%s.wav", s );
	} else {
		Q_strncpyz( buffer, s, sizeof(buffer) );
	}
	ent->noise_index = G_SoundIndex(buffer);

	// a repeating speaker can be done completely client side
	ent->s.eType = ET_SPEAKER;
	ent->s.eventParm = ent->noise_index;
	ent->s.frame = ent->wait * 10;
	ent->s.clientNum = ent->random * 10;


	// check for prestarted looping sound
	if ( ent->spawnflags & 1 ) {
		ent->s.loopSound = ent->noise_index;
	}

	ent->use = Use_Target_Speaker;

	if (ent->spawnflags & 4) {
		ent->r.svFlags |= SVF_BROADCAST;
	}

	VectorCopy( ent->s.origin, ent->s.pos.trBase );

	// must link the entity so we get areas and clusters so
	// the server can determine who to send updates to
	trap_LinkEntity( ent );
}