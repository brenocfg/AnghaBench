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
typedef  char wchar_t ;
struct write_file_data {int fd; int /*<<< orphan*/  filename; } ;
struct archive {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARCHIVE_ERRNO_MISC ; 
 int ARCHIVE_FAILED ; 
 int ARCHIVE_FATAL ; 
 scalar_t__ ENOMEM ; 
 int archive_mstring_copy_mbs (int /*<<< orphan*/ *,void const*) ; 
 int archive_mstring_copy_wcs (int /*<<< orphan*/ *,void const*) ; 
 int /*<<< orphan*/  archive_set_error (struct archive*,scalar_t__,char*,...) ; 
 int archive_write_open (struct archive*,struct write_file_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ calloc (int,int) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  file_close ; 
 int /*<<< orphan*/  file_open ; 
 int /*<<< orphan*/  file_write ; 

__attribute__((used)) static int
open_filename(struct archive *a, int mbs_fn, const void *filename)
{
	struct write_file_data *mine;
	int r;

	mine = (struct write_file_data *)calloc(1, sizeof(*mine));
	if (mine == NULL) {
		archive_set_error(a, ENOMEM, "No memory");
		return (ARCHIVE_FATAL);
	}
	if (mbs_fn)
		r = archive_mstring_copy_mbs(&mine->filename, filename);
	else
		r = archive_mstring_copy_wcs(&mine->filename, filename);
	if (r < 0) {
		if (errno == ENOMEM) {
			archive_set_error(a, ENOMEM, "No memory");
			return (ARCHIVE_FATAL);
		}
		if (mbs_fn)
			archive_set_error(a, ARCHIVE_ERRNO_MISC,
			    "Can't convert '%s' to WCS",
			    (const char *)filename);
		else
			archive_set_error(a, ARCHIVE_ERRNO_MISC,
			    "Can't convert '%S' to MBS",
			    (const wchar_t *)filename);
		return (ARCHIVE_FAILED);
	}
	mine->fd = -1;
	return (archive_write_open(a, mine,
		file_open, file_write, file_close));
}