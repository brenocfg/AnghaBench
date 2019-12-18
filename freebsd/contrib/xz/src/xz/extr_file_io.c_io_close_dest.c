#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int dest_fd; int /*<<< orphan*/  dest_name; int /*<<< orphan*/  dest_st; } ;
typedef  TYPE_1__ file_pair ;

/* Variables and functions */
 int /*<<< orphan*/  F_SETFL ; 
 int STDOUT_FILENO ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ close (int) ; 
 int /*<<< orphan*/  errno ; 
 int fcntl (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  io_unlink (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  message_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int restore_stdout_flags ; 
 int /*<<< orphan*/  stdout_flags ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
io_close_dest(file_pair *pair, bool success)
{
#ifndef TUKLIB_DOSLIKE
	// If io_open_dest() has disabled O_APPEND, restore it here.
	if (restore_stdout_flags) {
		assert(pair->dest_fd == STDOUT_FILENO);

		restore_stdout_flags = false;

		if (fcntl(STDOUT_FILENO, F_SETFL, stdout_flags) == -1) {
			message_error(_("Error restoring the O_APPEND flag "
					"to standard output: %s"),
					strerror(errno));
			return true;
		}
	}
#endif

	if (pair->dest_fd == -1 || pair->dest_fd == STDOUT_FILENO)
		return false;

	if (close(pair->dest_fd)) {
		message_error(_("%s: Closing the file failed: %s"),
				pair->dest_name, strerror(errno));

		// Closing destination file failed, so we cannot trust its
		// contents. Get rid of junk:
		io_unlink(pair->dest_name, &pair->dest_st);
		free(pair->dest_name);
		return true;
	}

	// If the operation using this file wasn't successful, we git rid
	// of the junk file.
	if (!success)
		io_unlink(pair->dest_name, &pair->dest_st);

	free(pair->dest_name);

	return false;
}