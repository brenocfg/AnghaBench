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
 int /*<<< orphan*/ * name_of_main ; 
 int /*<<< orphan*/  xfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * xstrdup (char const*) ; 

void
set_main_name (const char *name)
{
  if (name_of_main != NULL)
    {
      xfree (name_of_main);
      name_of_main = NULL;
    }
  if (name != NULL)
    {
      name_of_main = xstrdup (name);
    }
}