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

int setup_console ()
{
  #if defined (_WIN)
  SetConsoleWindowSize (132);

  if (_setmode (_fileno (stdin), _O_BINARY) == -1)
  {
    __mingw_fprintf (stderr, "%s: %m", "stdin");

    return -1;
  }

  if (_setmode (_fileno (stdout), _O_BINARY) == -1)
  {
    __mingw_fprintf (stderr, "%s: %m", "stdin");

    return -1;
  }

  if (_setmode (_fileno (stderr), _O_BINARY) == -1)
  {
    __mingw_fprintf (stderr, "%s: %m", "stdin");

    return -1;
  }
  #endif

  return 0;
}