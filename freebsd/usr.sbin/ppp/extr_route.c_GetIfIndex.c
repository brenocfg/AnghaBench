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
 int /*<<< orphan*/  Index2Nam (int) ; 
 int route_nifs ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

int
GetIfIndex(char *name)
{
  int idx;

  idx = 1;
  while (route_nifs == -1 || idx < route_nifs)
    if (strcmp(Index2Nam(idx), name) == 0)
      return idx;
    else
      idx++;
  return -1;
}