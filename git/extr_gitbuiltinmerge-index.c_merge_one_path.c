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
 int cache_name_pos (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  merge_entry (int,char const*) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

__attribute__((used)) static void merge_one_path(const char *path)
{
	int pos = cache_name_pos(path, strlen(path));

	/*
	 * If it already exists in the cache as stage0, it's
	 * already merged and there is nothing to do.
	 */
	if (pos < 0)
		merge_entry(-pos-1, path);
}