#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  char uint8_t ;
struct TYPE_7__ {scalar_t__ dest_pending_sparse; int dest_fd; int /*<<< orphan*/  dest_name; scalar_t__ dest_try_sparse; } ;
typedef  TYPE_1__ file_pair ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_CUR ; 
 int STDOUT_FILENO ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ io_close_dest (TYPE_1__*,int) ; 
 int /*<<< orphan*/  io_close_src (TYPE_1__*,int) ; 
 int /*<<< orphan*/  io_copy_attrs (TYPE_1__*) ; 
 scalar_t__ io_write_buf (TYPE_1__*,char const*,int) ; 
 int lseek (int,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  message_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  signals_block () ; 
 int /*<<< orphan*/  signals_unblock () ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

extern void
io_close(file_pair *pair, bool success)
{
	// Take care of sparseness at the end of the output file.
	if (success && pair->dest_try_sparse
			&& pair->dest_pending_sparse > 0) {
		// Seek forward one byte less than the size of the pending
		// hole, then write one zero-byte. This way the file grows
		// to its correct size. An alternative would be to use
		// ftruncate() but that isn't portable enough (e.g. it
		// doesn't work with FAT on Linux; FAT isn't that important
		// since it doesn't support sparse files anyway, but we don't
		// want to create corrupt files on it).
		if (lseek(pair->dest_fd, pair->dest_pending_sparse - 1,
				SEEK_CUR) == -1) {
			message_error(_("%s: Seeking failed when trying "
					"to create a sparse file: %s"),
					pair->dest_name, strerror(errno));
			success = false;
		} else {
			const uint8_t zero[1] = { '\0' };
			if (io_write_buf(pair, zero, 1))
				success = false;
		}
	}

	signals_block();

	// Copy the file attributes. We need to skip this if destination
	// file isn't open or it is standard output.
	if (success && pair->dest_fd != -1 && pair->dest_fd != STDOUT_FILENO)
		io_copy_attrs(pair);

	// Close the destination first. If it fails, we must not remove
	// the source file!
	if (io_close_dest(pair, success))
		success = false;

	// Close the source file, and unlink it if the operation using this
	// file pair was successful and we haven't requested to keep the
	// source file.
	io_close_src(pair, success);

	signals_unblock();

	return;
}