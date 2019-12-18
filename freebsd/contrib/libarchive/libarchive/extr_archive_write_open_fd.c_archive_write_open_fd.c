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
struct archive {int dummy; } ;

/* Variables and functions */
 int ARCHIVE_FATAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  O_BINARY ; 
 int /*<<< orphan*/  archive_set_error (struct archive*,int /*<<< orphan*/ ,char*) ; 
 int archive_write_open (struct archive*,struct write_fd_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  file_close ; 
 int /*<<< orphan*/  file_open ; 
 int /*<<< orphan*/  file_write ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  setmode (int,int /*<<< orphan*/ ) ; 

int
archive_write_open_fd(struct archive *a, int fd)
{
	struct write_fd_data *mine;

	mine = (struct write_fd_data *)malloc(sizeof(*mine));
	if (mine == NULL) {
		archive_set_error(a, ENOMEM, "No memory");
		return (ARCHIVE_FATAL);
	}
	mine->fd = fd;
#if defined(__CYGWIN__) || defined(_WIN32)
	setmode(mine->fd, O_BINARY);
#endif
	return (archive_write_open(a, mine,
		    file_open, file_write, file_close));
}