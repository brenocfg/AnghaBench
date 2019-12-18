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
 int /*<<< orphan*/  setproctitle (char*,...) ; 

void
SetTitle(const char *title)
{
  if (title == NULL)
    setproctitle(NULL);
  else if (title[0] == '-' && title[1] != '\0')
    setproctitle("-%s", title + 1);
  else
    setproctitle("%s", title);
}