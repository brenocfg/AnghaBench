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
 scalar_t__ immediate_quit ; 
 int /*<<< orphan*/  quit () ; 
 int quit_flag ; 
 int /*<<< orphan*/  signal (int,void (*) (int)) ; 

void
request_quit (int signo)
{
  quit_flag = 1;
  /* Restore the signal handler.  Harmless with BSD-style signals, needed
     for System V-style signals.  So just always do it, rather than worrying
     about USG defines and stuff like that.  */
  signal (signo, request_quit);

  if (immediate_quit)
    quit ();
}