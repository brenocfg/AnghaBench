#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int /*<<< orphan*/  S_Base_ClearSoundBuffer () ; 
 int /*<<< orphan*/  S_Base_StopBackgroundTrack () ; 
 int /*<<< orphan*/  s_soundStarted ; 

void S_Base_StopAllSounds(void) {
	if ( !s_soundStarted ) {
		return;
	}

	// stop the background music
	S_Base_StopBackgroundTrack();

	S_Base_ClearSoundBuffer ();
}