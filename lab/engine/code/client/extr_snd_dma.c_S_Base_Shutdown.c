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
 int /*<<< orphan*/  Cmd_RemoveCommand (char*) ; 
 int /*<<< orphan*/  SNDDMA_Shutdown () ; 
 int /*<<< orphan*/  SND_shutdown () ; 
 scalar_t__ s_numSfx ; 
 scalar_t__ s_soundStarted ; 

void S_Base_Shutdown( void ) {
	if ( !s_soundStarted ) {
		return;
	}

	SNDDMA_Shutdown();
	SND_shutdown();

	s_soundStarted = 0;
	s_numSfx = 0;

	Cmd_RemoveCommand("s_info");
}