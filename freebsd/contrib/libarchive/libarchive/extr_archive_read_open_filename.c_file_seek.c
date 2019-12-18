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
struct read_file_data {scalar_t__ filename_type; TYPE_1__ filename; int /*<<< orphan*/  fd; } ;
struct archive {int dummy; } ;
typedef  scalar_t__ int64_t ;

/* Variables and functions */
 scalar_t__ ARCHIVE_FATAL ; 
 scalar_t__ FNT_MBS ; 
 scalar_t__ FNT_STDIN ; 
 int /*<<< orphan*/  archive_set_error (struct archive*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ lseek (int /*<<< orphan*/ ,scalar_t__,int) ; 

__attribute__((used)) static int64_t
file_seek(struct archive *a, void *client_data, int64_t request, int whence)
{
	struct read_file_data *mine = (struct read_file_data *)client_data;
	int64_t r;

	/* We use off_t here because lseek() is declared that way. */
	/* See above for notes about when off_t is less than 64 bits. */
	r = lseek(mine->fd, request, whence);
	if (r >= 0)
		return r;

	/* If the input is corrupted or truncated, fail. */
	if (mine->filename_type == FNT_STDIN)
		archive_set_error(a, errno, "Error seeking in stdin");
	else if (mine->filename_type == FNT_MBS)
		archive_set_error(a, errno, "Error seeking in '%s'",
		    mine->filename.m);
	else
		archive_set_error(a, errno, "Error seeking in '%S'",
		    mine->filename.w);
	return (ARCHIVE_FATAL);
}