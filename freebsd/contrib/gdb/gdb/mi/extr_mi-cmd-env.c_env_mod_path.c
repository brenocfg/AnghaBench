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
 int /*<<< orphan*/  add_path (char*,char**,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
env_mod_path (char *dirname, char **which_path)
{
  if (dirname == 0 || dirname[0] == '\0')
    return;

  /* Call add_path with last arg 0 to indicate not to parse for 
     separator characters.  */
  add_path (dirname, which_path, 0);
}