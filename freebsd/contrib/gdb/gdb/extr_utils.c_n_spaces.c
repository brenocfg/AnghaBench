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
 int /*<<< orphan*/  xfree (char*) ; 
 scalar_t__ xmalloc (int) ; 

char *
n_spaces (int n)
{
  char *t;
  static char *spaces = 0;
  static int max_spaces = -1;

  if (n > max_spaces)
    {
      if (spaces)
	xfree (spaces);
      spaces = (char *) xmalloc (n + 1);
      for (t = spaces + n; t != spaces;)
	*--t = ' ';
      spaces[n] = '\0';
      max_spaces = n;
    }

  return spaces + max_spaces - n;
}