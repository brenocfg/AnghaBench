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
 int ABORT_CHAR ; 
 int RUBOUT ; 
 int /*<<< orphan*/  beep () ; 
 int rl_read_key () ; 

__attribute__((used)) static int
get_y_or_n (void)
{
  extern int _rl_abort_internal ();
  int c;

  for (;;)
    {
      c = rl_read_key ();
      if (c == 'y' || c == 'Y' || c == ' ')
	return (1);
      if (c == 'n' || c == 'N' || c == RUBOUT)
	return (0);
      if (c == ABORT_CHAR)
	_rl_abort_internal ();
      beep ();
    }
}