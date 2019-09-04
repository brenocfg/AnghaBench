#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int watertype; TYPE_2__* client; scalar_t__ waterlevel; } ;
typedef  TYPE_3__ gentity_t ;
struct TYPE_9__ {scalar_t__ snd_fry; } ;
struct TYPE_6__ {scalar_t__ loopSound; } ;
struct TYPE_7__ {TYPE_1__ ps; } ;

/* Variables and functions */
 int CONTENTS_LAVA ; 
 int CONTENTS_SLIME ; 
 TYPE_4__ level ; 

void G_SetClientSound( gentity_t *ent ) {
#ifdef MISSIONPACK
	if( ent->s.eFlags & EF_TICKING ) {
		ent->client->ps.loopSound = G_SoundIndex( "sound/weapons/proxmine/wstbtick.wav");
	}
	else
#endif
	if (ent->waterlevel && (ent->watertype&(CONTENTS_LAVA|CONTENTS_SLIME)) ) {
		ent->client->ps.loopSound = level.snd_fry;
	} else {
		ent->client->ps.loopSound = 0;
	}
}