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
struct write_fd_data {int fd; } ;
struct stat {int /*<<< orphan*/  st_mode; int /*<<< orphan*/  st_ino; int /*<<< orphan*/  st_dev; } ;
struct archive {int dummy; } ;

/* Variables and functions */
 int ARCHIVE_FATAL ; 
 int ARCHIVE_OK ; 
 scalar_t__ S_ISBLK (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISCHR (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISFIFO (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISREG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  archive_set_error (struct archive*,int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ archive_write_get_bytes_in_last_block (struct archive*) ; 
 int /*<<< orphan*/  archive_write_set_bytes_in_last_block (struct archive*,int) ; 
 int /*<<< orphan*/  archive_write_set_skip_file (struct archive*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ fstat (int,struct stat*) ; 

__attribute__((used)) static int
file_open(struct archive *a, void *client_data)
{
	struct write_fd_data *mine;
	struct stat st;

	mine = (struct write_fd_data *)client_data;

	if (fstat(mine->fd, &st) != 0) {
		archive_set_error(a, errno, "Couldn't stat fd %d", mine->fd);
		return (ARCHIVE_FATAL);
	}

	/*
	 * If this is a regular file, don't add it to itself.
	 */
	if (S_ISREG(st.st_mode))
		archive_write_set_skip_file(a, st.st_dev, st.st_ino);

	/*
	 * If client hasn't explicitly set the last block handling,
	 * then set it here.
	 */
	if (archive_write_get_bytes_in_last_block(a) < 0) {
		/* If the output is a block or character device, fifo,
		 * or stdout, pad the last block, otherwise leave it
		 * unpadded. */
		if (S_ISCHR(st.st_mode) || S_ISBLK(st.st_mode) ||
		    S_ISFIFO(st.st_mode) || (mine->fd == 1))
			/* Last block will be fully padded. */
			archive_write_set_bytes_in_last_block(a, 0);
		else
			archive_write_set_bytes_in_last_block(a, 1);
	}

	return (ARCHIVE_OK);
}