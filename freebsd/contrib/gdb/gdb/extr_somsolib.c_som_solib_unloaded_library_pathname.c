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
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  som_solib_have_unload_event (int) ; 
 char* som_solib_library_pathname (int) ; 

char *
som_solib_unloaded_library_pathname (int pid)
{
  if (!som_solib_have_unload_event (pid))
    error ("Must have an unload event to use this query");

  return som_solib_library_pathname (pid);
}