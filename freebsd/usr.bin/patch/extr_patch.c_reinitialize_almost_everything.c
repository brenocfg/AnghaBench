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
 scalar_t__ diff_type ; 
 int /*<<< orphan*/ ** filearg ; 
 scalar_t__ filec ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_some_switches () ; 
 scalar_t__ input_lines ; 
 scalar_t__ last_frozen_line ; 
 scalar_t__ last_offset ; 
 int /*<<< orphan*/  out_of_mem ; 
 int /*<<< orphan*/ * outname ; 
 int /*<<< orphan*/  re_input () ; 
 int /*<<< orphan*/  re_patch () ; 
 int /*<<< orphan*/  reverse ; 
 int /*<<< orphan*/  reverse_flag_specified ; 
 int /*<<< orphan*/ * revision ; 
 int skip_rest_of_patch ; 
 int /*<<< orphan*/ * source_file ; 

__attribute__((used)) static void
reinitialize_almost_everything(void)
{
	re_patch();
	re_input();

	input_lines = 0;
	last_frozen_line = 0;

	filec = 0;
	if (!out_of_mem) {
		free(filearg[0]);
		filearg[0] = NULL;
	}

	free(source_file);
	source_file = NULL;

	free(outname);
	outname = NULL;

	last_offset = 0;
	diff_type = 0;

	free(revision);
	revision = NULL;

	reverse = reverse_flag_specified;
	skip_rest_of_patch = false;

	get_some_switches();
}