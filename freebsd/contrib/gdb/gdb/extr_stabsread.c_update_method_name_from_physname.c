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
 int /*<<< orphan*/  complaint (int /*<<< orphan*/ *,char*,char*) ; 
 char* method_name_from_physname (char*) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  symfile_complaints ; 
 int /*<<< orphan*/  xfree (char*) ; 

__attribute__((used)) static void
update_method_name_from_physname (char **old_name, char *physname)
{
  char *method_name;

  method_name = method_name_from_physname (physname);

  if (method_name == NULL)
    {
      complaint (&symfile_complaints,
		 "Method has bad physname %s\n", physname);
      return;
    }

  if (strcmp (*old_name, method_name) != 0)
    {
      xfree (*old_name);
      *old_name = method_name;
    }
  else
    xfree (method_name);
}