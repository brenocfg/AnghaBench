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
 int /*<<< orphan*/  allow_remove ; 
 int error (char*,char const*) ; 
 scalar_t__ remove_file_from_cache (char const*) ; 

__attribute__((used)) static int remove_one_path(const char *path)
{
	if (!allow_remove)
		return error("%s: does not exist and --remove not passed", path);
	if (remove_file_from_cache(path))
		return error("%s: cannot remove from the index", path);
	return 0;
}