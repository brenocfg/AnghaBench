#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_9__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {int ownerNum; int /*<<< orphan*/  currentOrigin; int /*<<< orphan*/  contents; int /*<<< orphan*/  absmax; int /*<<< orphan*/  absmin; int /*<<< orphan*/  maxs; int /*<<< orphan*/  mins; int /*<<< orphan*/  svFlags; } ;
struct TYPE_14__ {int /*<<< orphan*/  trBase; int /*<<< orphan*/  trType; int /*<<< orphan*/  trDelta; scalar_t__ trTime; } ;
struct TYPE_15__ {int eFlags; int number; scalar_t__ groundEntityNum; int legsAnim; int torsoAnim; TYPE_3__ pos; scalar_t__ event; scalar_t__ loopSound; scalar_t__ powerups; int /*<<< orphan*/  origin; } ;
struct TYPE_17__ {int clipmask; scalar_t__ health; TYPE_5__ r; TYPE_4__ s; void* takedamage; int /*<<< orphan*/  die; int /*<<< orphan*/  think; scalar_t__ nextthink; TYPE_2__* client; scalar_t__ physicsBounce; void* physicsObject; scalar_t__ timestamp; struct TYPE_17__* activator; int /*<<< orphan*/  classname; int /*<<< orphan*/  inuse; } ;
typedef  TYPE_6__ gentity_t ;
struct TYPE_18__ {size_t bodyQueIndex; int num_entities; scalar_t__ time; TYPE_6__** bodyQue; } ;
struct TYPE_12__ {int /*<<< orphan*/  velocity; } ;
struct TYPE_13__ {TYPE_1__ ps; } ;

/* Variables and functions */
 int ANIM_TOGGLEBIT ; 
 int BODY_QUEUE_SIZE ; 
#define  BOTH_DEAD1 133 
#define  BOTH_DEAD2 132 
#define  BOTH_DEAD3 131 
#define  BOTH_DEATH1 130 
#define  BOTH_DEATH2 129 
#define  BOTH_DEATH3 128 
 int /*<<< orphan*/  BodySink ; 
 int /*<<< orphan*/  CONTENTS_CORPSE ; 
 int CONTENTS_NODROP ; 
 int CONTENTS_PLAYERCLIP ; 
 int CONTENTS_SOLID ; 
 int EF_DEAD ; 
 int EF_KAMIKAZE ; 
 scalar_t__ ENTITYNUM_NONE ; 
 scalar_t__ GIB_HEALTH ; 
 int /*<<< orphan*/  TR_GRAVITY ; 
 int /*<<< orphan*/  TR_STATIONARY ; 
 int /*<<< orphan*/  VectorCopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  body_die ; 
 TYPE_6__* g_entities ; 
 TYPE_9__ level ; 
 void* qfalse ; 
 void* qtrue ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  trap_LinkEntity (TYPE_6__*) ; 
 int trap_PointContents (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  trap_UnlinkEntity (TYPE_6__*) ; 

void CopyToBodyQue( gentity_t *ent ) {
#ifdef MISSIONPACK
	gentity_t	*e;
	int i;
#endif
	gentity_t		*body;
	int			contents;

	trap_UnlinkEntity (ent);

	// if client is in a nodrop area, don't leave the body
	contents = trap_PointContents( ent->s.origin, -1 );
	if ( contents & CONTENTS_NODROP ) {
		return;
	}

	// grab a body que and cycle to the next one
	body = level.bodyQue[ level.bodyQueIndex ];
	level.bodyQueIndex = (level.bodyQueIndex + 1) % BODY_QUEUE_SIZE;

	body->s = ent->s;
	body->s.eFlags = EF_DEAD;		// clear EF_TALK, etc
#ifdef MISSIONPACK
	if ( ent->s.eFlags & EF_KAMIKAZE ) {
		body->s.eFlags |= EF_KAMIKAZE;

		// check if there is a kamikaze timer around for this owner
		for (i = 0; i < level.num_entities; i++) {
			e = &g_entities[i];
			if (!e->inuse)
				continue;
			if (e->activator != ent)
				continue;
			if (strcmp(e->classname, "kamikaze timer"))
				continue;
			e->activator = body;
			break;
		}
	}
#endif
	body->s.powerups = 0;	// clear powerups
	body->s.loopSound = 0;	// clear lava burning
	body->s.number = body - g_entities;
	body->timestamp = level.time;
	body->physicsObject = qtrue;
	body->physicsBounce = 0;		// don't bounce
	if ( body->s.groundEntityNum == ENTITYNUM_NONE ) {
		body->s.pos.trType = TR_GRAVITY;
		body->s.pos.trTime = level.time;
		VectorCopy( ent->client->ps.velocity, body->s.pos.trDelta );
	} else {
		body->s.pos.trType = TR_STATIONARY;
	}
	body->s.event = 0;

	// change the animation to the last-frame only, so the sequence
	// doesn't repeat anew for the body
	switch ( body->s.legsAnim & ~ANIM_TOGGLEBIT ) {
	case BOTH_DEATH1:
	case BOTH_DEAD1:
		body->s.torsoAnim = body->s.legsAnim = BOTH_DEAD1;
		break;
	case BOTH_DEATH2:
	case BOTH_DEAD2:
		body->s.torsoAnim = body->s.legsAnim = BOTH_DEAD2;
		break;
	case BOTH_DEATH3:
	case BOTH_DEAD3:
	default:
		body->s.torsoAnim = body->s.legsAnim = BOTH_DEAD3;
		break;
	}

	body->r.svFlags = ent->r.svFlags;
	VectorCopy (ent->r.mins, body->r.mins);
	VectorCopy (ent->r.maxs, body->r.maxs);
	VectorCopy (ent->r.absmin, body->r.absmin);
	VectorCopy (ent->r.absmax, body->r.absmax);

	body->clipmask = CONTENTS_SOLID | CONTENTS_PLAYERCLIP;
	body->r.contents = CONTENTS_CORPSE;
	body->r.ownerNum = ent->s.number;

	body->nextthink = level.time + 5000;
	body->think = BodySink;

	body->die = body_die;

	// don't take more damage if already gibbed
	if ( ent->health <= GIB_HEALTH ) {
		body->takedamage = qfalse;
	} else {
		body->takedamage = qtrue;
	}


	VectorCopy ( body->s.pos.trBase, body->r.currentOrigin );
	trap_LinkEntity (body);
}