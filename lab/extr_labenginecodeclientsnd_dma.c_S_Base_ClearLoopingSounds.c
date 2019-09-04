#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ qboolean ;
struct TYPE_4__ {scalar_t__ kill; TYPE_1__* sfx; } ;
struct TYPE_3__ {scalar_t__ soundLength; } ;

/* Variables and functions */
 int MAX_GENTITIES ; 
 int /*<<< orphan*/  S_Base_StopLoopingSound (int) ; 
 TYPE_2__* loopSounds ; 
 scalar_t__ numLoopChannels ; 
 scalar_t__ qtrue ; 

void S_Base_ClearLoopingSounds( qboolean killall ) {
	int i;
	for ( i = 0 ; i < MAX_GENTITIES ; i++) {
		if (killall || loopSounds[i].kill == qtrue || (loopSounds[i].sfx && loopSounds[i].sfx->soundLength == 0)) {
			S_Base_StopLoopingSound(i);
		}
	}
	numLoopChannels = 0;
}