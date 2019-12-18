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
 int /*<<< orphan*/  FATAL (char*) ; 
 char* getenv (char*) ; 
 scalar_t__ snprintf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 
 char* xmalloc (scalar_t__) ; 

char *
get_home (void)
{
  char *user_home = NULL, *path = NULL;

  user_home = getenv ("HOME");
  if (user_home == NULL)
    FATAL ("Unable to determine the HOME environment variable.");

  path = xmalloc (snprintf (NULL, 0, "%s/.goaccessrc", user_home) + 1);
  sprintf (path, "%s/.goaccessrc", user_home);

  return path;
}