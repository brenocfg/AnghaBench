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
 scalar_t__ MODE_LIST ; 
 scalar_t__ V_VERBOSE ; 
 int current_filename_printed ; 
 char const* filename ; 
 int /*<<< orphan*/  files_pos ; 
 scalar_t__ opt_mode ; 
 int /*<<< orphan*/  print_filename () ; 
 scalar_t__ progress_automatic ; 
 scalar_t__ verbosity ; 

extern void
message_filename(const char *src_name)
{
	// Start numbering the files starting from one.
	++files_pos;
	filename = src_name;

	if (verbosity >= V_VERBOSE
			&& (progress_automatic || opt_mode == MODE_LIST))
		print_filename();
	else
		current_filename_printed = false;

	return;
}