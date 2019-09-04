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
typedef  int /*<<< orphan*/  gpointer ;
typedef  int /*<<< orphan*/  gboolean ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  gtk_main_quit () ; 
 scalar_t__ iteration ; 
 scalar_t__ stepsIteration ; 
 int /*<<< orphan*/  stepsQuit ; 

__attribute__((used)) static gboolean quit(gpointer data)
{
	if (iteration == stepsIteration)
		stepsQuit = TRUE;
		// TODO run a gtk_main() here just to do the cleanup steps of syncing the clipboard and other stuff gtk_main() does before it returns
	else
		gtk_main_quit();
	return FALSE;
}