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
typedef  int /*<<< orphan*/  fusefs_dot ;

/* Variables and functions */
 scalar_t__ strcmp (char const*,char const*) ; 
 scalar_t__ strncmp (char const*,char const*,int) ; 

__attribute__((used)) static bool
are_fusefs(const char *fsname, const char *vfc_name)
{
	const static char fusefs[] = "fusefs";
	const static char fusefs_dot[] = "fusefs.";

	return (strncmp(fsname, fusefs_dot, sizeof(fusefs_dot) - 1) == 0 &&
	    strcmp(fusefs, vfc_name) == 0);
}