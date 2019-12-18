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
struct progress {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  display_progress (struct progress*,int) ; 
 int /*<<< orphan*/  for_each_loose_file_in_objdir (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct progress*) ; 
 int /*<<< orphan*/  fprintf_ln (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fsck_cruft ; 
 int /*<<< orphan*/  fsck_loose ; 
 int /*<<< orphan*/  fsck_subdir ; 
 scalar_t__ show_progress ; 
 struct progress* start_progress (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stop_progress (struct progress**) ; 
 scalar_t__ verbose ; 

__attribute__((used)) static void fsck_object_dir(const char *path)
{
	struct progress *progress = NULL;

	if (verbose)
		fprintf_ln(stderr, _("Checking object directory"));

	if (show_progress)
		progress = start_progress(_("Checking object directories"), 256);

	for_each_loose_file_in_objdir(path, fsck_loose, fsck_cruft, fsck_subdir,
				      progress);
	display_progress(progress, 256);
	stop_progress(&progress);
}