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

int
get_dataset_depth(const char *path)
{
	const char *loc = path;
	int nesting = 0;

	/*
	 * Keep track of nesting until you hit the end of the
	 * path or found the snapshot/bookmark seperator.
	 */
	for (int i = 0; loc[i] != '\0' &&
	    loc[i] != '@' &&
	    loc[i] != '#'; i++) {
		if (loc[i] == '/')
			nesting++;
	}

	return (nesting);
}