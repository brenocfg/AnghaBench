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
 scalar_t__ check_object (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  display_progress (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  get_indexed_object (unsigned int) ; 
 unsigned int get_max_object_index () ; 
 int /*<<< orphan*/  progress ; 
 int /*<<< orphan*/  start_delayed_progress (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  stop_progress (int /*<<< orphan*/ *) ; 
 scalar_t__ verbose ; 

__attribute__((used)) static unsigned check_objects(void)
{
	unsigned i, max, foreign_nr = 0;

	max = get_max_object_index();

	if (verbose)
		progress = start_delayed_progress(_("Checking objects"), max);

	for (i = 0; i < max; i++) {
		foreign_nr += check_object(get_indexed_object(i));
		display_progress(progress, i + 1);
	}

	stop_progress(&progress);
	return foreign_nr;
}