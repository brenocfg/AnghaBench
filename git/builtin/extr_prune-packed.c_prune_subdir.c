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
 int PRUNE_PACKED_DRY_RUN ; 
 int /*<<< orphan*/  display_progress (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  progress ; 
 int /*<<< orphan*/  rmdir (char const*) ; 

__attribute__((used)) static int prune_subdir(unsigned int nr, const char *path, void *data)
{
	int *opts = data;
	display_progress(progress, nr + 1);
	if (!(*opts & PRUNE_PACKED_DRY_RUN))
		rmdir(path);
	return 0;
}