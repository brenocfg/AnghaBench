#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ mouse_support; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUTTON1_CLICKED ; 
 scalar_t__ ERR ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  LOG_DEBUG (char*) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  clear () ; 
 TYPE_1__ conf ; 
 scalar_t__ curs_set (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  halfdelay (int) ; 
 int /*<<< orphan*/  initscr () ; 
 int /*<<< orphan*/  intrflush (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  keypad (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mousemask (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  noecho () ; 
 int /*<<< orphan*/  nonl () ; 
 int /*<<< orphan*/  stdscr ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

void
set_input_opts (void)
{
  initscr ();
  clear ();
  noecho ();
  halfdelay (10);
  nonl ();
  intrflush (stdscr, FALSE);
  keypad (stdscr, TRUE);
  if (curs_set (0) == ERR)
    LOG_DEBUG (("Unable to change cursor: %s\n", strerror (errno)));

  if (conf.mouse_support)
    mousemask (BUTTON1_CLICKED, NULL);
}