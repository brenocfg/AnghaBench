#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  w; int /*<<< orphan*/  m; } ;
struct read_file_data {void* buffer; scalar_t__ filename_type; TYPE_1__ filename; int /*<<< orphan*/  block_size; int /*<<< orphan*/  fd; } ;
struct archive {int dummy; } ;
typedef  scalar_t__ ssize_t ;

/* Variables and functions */
 scalar_t__ EINTR ; 
 scalar_t__ FNT_MBS ; 
 scalar_t__ FNT_STDIN ; 
 int /*<<< orphan*/  archive_set_error (struct archive*,scalar_t__,char*,...) ; 
 scalar_t__ errno ; 
 scalar_t__ read (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t
file_read(struct archive *a, void *client_data, const void **buff)
{
	struct read_file_data *mine = (struct read_file_data *)client_data;
	ssize_t bytes_read;

	/* TODO: If a recent lseek() operation has left us
	 * mis-aligned, read and return a short block to try to get
	 * us back in alignment. */

	/* TODO: Someday, try mmap() here; if that succeeds, give
	 * the entire file to libarchive as a single block.  That
	 * could be a lot faster than block-by-block manual I/O. */

	/* TODO: We might be able to improve performance on pipes and
	 * sockets by setting non-blocking I/O and just accepting
	 * whatever we get here instead of waiting for a full block
	 * worth of data. */

	*buff = mine->buffer;
	for (;;) {
		bytes_read = read(mine->fd, mine->buffer, mine->block_size);
		if (bytes_read < 0) {
			if (errno == EINTR)
				continue;
			else if (mine->filename_type == FNT_STDIN)
				archive_set_error(a, errno,
				    "Error reading stdin");
			else if (mine->filename_type == FNT_MBS)
				archive_set_error(a, errno,
				    "Error reading '%s'", mine->filename.m);
			else
				archive_set_error(a, errno,
				    "Error reading '%S'", mine->filename.w);
		}
		return (bytes_read);
	}
}