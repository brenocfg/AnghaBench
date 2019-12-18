#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  idx; } ;
typedef  TYPE_1__ xz_file_info ;
typedef  int /*<<< orphan*/  file_pair ;

/* Variables and functions */
 scalar_t__ FORMAT_AUTO ; 
 scalar_t__ FORMAT_XZ ; 
 scalar_t__ V_WARNING ; 
 TYPE_1__ XZ_FILE_INFO_INIT ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  io_close (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * io_open_src (char const*) ; 
 int /*<<< orphan*/  lzma_index_end (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  message_error (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  message_fatal (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  message_filename (char const*) ; 
 scalar_t__ message_verbosity_get () ; 
 int opt_force ; 
 scalar_t__ opt_format ; 
 scalar_t__ opt_robot ; 
 int opt_stdout ; 
 int /*<<< orphan*/  parse_indexes (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int print_info_adv (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int print_info_basic (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int print_info_robot (TYPE_1__*,int /*<<< orphan*/ *) ; 
 char const* stdin_filename ; 
 int /*<<< orphan*/  update_totals (TYPE_1__*) ; 

extern void
list_file(const char *filename)
{
	if (opt_format != FORMAT_XZ && opt_format != FORMAT_AUTO)
		message_fatal(_("--list works only on .xz files "
				"(--format=xz or --format=auto)"));

	message_filename(filename);

	if (filename == stdin_filename) {
		message_error(_("--list does not support reading from "
				"standard input"));
		return;
	}

	// Unset opt_stdout so that io_open_src() won't accept special files.
	// Set opt_force so that io_open_src() will follow symlinks.
	opt_stdout = false;
	opt_force = true;
	file_pair *pair = io_open_src(filename);
	if (pair == NULL)
		return;

	xz_file_info xfi = XZ_FILE_INFO_INIT;
	if (!parse_indexes(&xfi, pair)) {
		bool fail;

		// We have three main modes:
		//  - --robot, which has submodes if --verbose is specified
		//    once or twice
		//  - Normal --list without --verbose
		//  - --list with one or two --verbose
		if (opt_robot)
			fail = print_info_robot(&xfi, pair);
		else if (message_verbosity_get() <= V_WARNING)
			fail = print_info_basic(&xfi, pair);
		else
			fail = print_info_adv(&xfi, pair);

		// Update the totals that are displayed after all
		// the individual files have been listed. Don't count
		// broken files.
		if (!fail)
			update_totals(&xfi);

		lzma_index_end(xfi.idx, NULL);
	}

	io_close(pair, false);
	return;
}