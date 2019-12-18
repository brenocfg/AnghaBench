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
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  die_errno (int /*<<< orphan*/ ,char const*) ; 
 char* get_mtime_path (char const*) ; 
 scalar_t__ rmdir (char const*) ; 

__attribute__((used)) static void xrmdir(const char *path)
{
	path = get_mtime_path(path);
	if (rmdir(path))
		die_errno(_("failed to delete directory %s"), path);
}