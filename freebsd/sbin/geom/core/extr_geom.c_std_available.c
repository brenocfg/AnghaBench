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
 int /*<<< orphan*/  assert (int) ; 
 int std_list_available () ; 
 int std_load_available () ; 
 int std_status_available () ; 
 int std_unload_available () ; 
 scalar_t__ strcmp (char const*,char*) ; 

__attribute__((used)) static int
std_available(const char *name)
{

	if (strcmp(name, "help") == 0)
		return (1);
	else if (strcmp(name, "list") == 0)
		return (std_list_available());
	else if (strcmp(name, "status") == 0)
		return (std_status_available());
	else if (strcmp(name, "load") == 0)
		return (std_load_available());
	else if (strcmp(name, "unload") == 0)
		return (std_unload_available());
	else
		assert(!"Unknown standard command.");
	return (0);
}