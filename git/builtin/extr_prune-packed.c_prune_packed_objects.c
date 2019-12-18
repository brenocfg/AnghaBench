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
 int PRUNE_PACKED_VERBOSE ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  display_progress (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  for_each_loose_file_in_objdir (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  get_object_directory () ; 
 int /*<<< orphan*/  progress ; 
 int /*<<< orphan*/  prune_object ; 
 int /*<<< orphan*/  prune_subdir ; 
 int /*<<< orphan*/  start_delayed_progress (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stop_progress (int /*<<< orphan*/ *) ; 

void prune_packed_objects(int opts)
{
	if (opts & PRUNE_PACKED_VERBOSE)
		progress = start_delayed_progress(_("Removing duplicate objects"), 256);

	for_each_loose_file_in_objdir(get_object_directory(),
				      prune_object, NULL, prune_subdir, &opts);

	/* Ensure we show 100% before finishing progress */
	display_progress(progress, 256);
	stop_progress(&progress);
}