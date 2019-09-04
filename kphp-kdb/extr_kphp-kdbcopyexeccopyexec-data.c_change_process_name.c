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
 int /*<<< orphan*/  PR_SET_NAME ; 
 int argc_copy ; 
 char** argv_copy ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ prctl (int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  strncpy (char*,char*,int) ; 
 int /*<<< orphan*/  vkprintf (int,char*,char*) ; 

void change_process_name (char *new_name) {
  /* change process name in top */
  if (prctl (PR_SET_NAME, (unsigned long) new_name, 0, 0, 0) < 0) {
    vkprintf (1, "changing process name to %s failed. %m\n", new_name);
  }
  /* change process name in ps */
  int i;
  for (i = 1; i < argc_copy; i++) {
    memset (argv_copy[i], 0, strlen (argv_copy[i]));
  }
  i = strlen (new_name) - strlen (argv_copy[0]);
  if (i < 0) {
    i = 0;
  }
  strncpy (argv_copy[0], new_name + i, strlen (argv_copy[0]));
}