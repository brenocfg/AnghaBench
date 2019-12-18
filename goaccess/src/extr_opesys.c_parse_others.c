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

__attribute__((used)) static char *
parse_others (char *agent, int spaces)
{
  char *p;
  int space = 0;
  p = agent;
  /* assume the following chars are within the given agent */
  while (*p != ';' && *p != ')' && *p != '(' && *p != '\0') {
    if (*p == ' ')
      space++;
    if (space > spaces)
      break;
    p++;
  }
  *p = 0;

  return agent;
}