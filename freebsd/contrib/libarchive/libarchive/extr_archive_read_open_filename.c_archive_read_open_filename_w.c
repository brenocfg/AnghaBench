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
typedef  int wchar_t ;
struct TYPE_2__ {int /*<<< orphan*/  m; int /*<<< orphan*/  w; } ;
struct read_file_data {int fd; size_t block_size; TYPE_1__ filename; int /*<<< orphan*/  filename_type; } ;
struct archive_string {int /*<<< orphan*/  s; } ;
struct archive {int dummy; } ;

/* Variables and functions */
 int ARCHIVE_FATAL ; 
 scalar_t__ ARCHIVE_OK ; 
 scalar_t__ EINVAL ; 
 scalar_t__ ENOMEM ; 
 int /*<<< orphan*/  FNT_MBS ; 
 int /*<<< orphan*/  FNT_STDIN ; 
 int /*<<< orphan*/  FNT_WCS ; 
 scalar_t__ archive_read_append_callback_data (struct archive*,struct read_file_data*) ; 
 int archive_read_open1 (struct archive*) ; 
 int /*<<< orphan*/  archive_read_set_close_callback (struct archive*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  archive_read_set_open_callback (struct archive*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  archive_read_set_read_callback (struct archive*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  archive_read_set_seek_callback (struct archive*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  archive_read_set_skip_callback (struct archive*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  archive_read_set_switch_callback (struct archive*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  archive_set_error (struct archive*,scalar_t__,char*) ; 
 scalar_t__ archive_string_append_from_wcs (struct archive_string*,int const*,int) ; 
 int /*<<< orphan*/  archive_string_free (struct archive_string*) ; 
 int /*<<< orphan*/  archive_string_init (struct archive_string*) ; 
 scalar_t__ calloc (int,int) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  file_close ; 
 int /*<<< orphan*/  file_open ; 
 int /*<<< orphan*/  file_read ; 
 int /*<<< orphan*/  file_seek ; 
 int /*<<< orphan*/  file_skip ; 
 int /*<<< orphan*/  file_switch ; 
 int /*<<< orphan*/  free (struct read_file_data*) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wcscpy (int /*<<< orphan*/ ,int const*) ; 
 int wcslen (int const*) ; 

int
archive_read_open_filename_w(struct archive *a, const wchar_t *wfilename,
    size_t block_size)
{
	struct read_file_data *mine = (struct read_file_data *)calloc(1,
		sizeof(*mine) + wcslen(wfilename) * sizeof(wchar_t));
	if (!mine)
	{
		archive_set_error(a, ENOMEM, "No memory");
		return (ARCHIVE_FATAL);
	}
	mine->fd = -1;
	mine->block_size = block_size;

	if (wfilename == NULL || wfilename[0] == L'\0') {
		mine->filename_type = FNT_STDIN;
	} else {
#if defined(_WIN32) && !defined(__CYGWIN__)
		mine->filename_type = FNT_WCS;
		wcscpy(mine->filename.w, wfilename);
#else
		/*
		 * POSIX system does not support a wchar_t interface for
		 * open() system call, so we have to translate a wchar_t
		 * filename to multi-byte one and use it.
		 */
		struct archive_string fn;

		archive_string_init(&fn);
		if (archive_string_append_from_wcs(&fn, wfilename,
		    wcslen(wfilename)) != 0) {
			if (errno == ENOMEM)
				archive_set_error(a, errno,
				    "Can't allocate memory");
			else
				archive_set_error(a, EINVAL,
				    "Failed to convert a wide-character"
				    " filename to a multi-byte filename");
			archive_string_free(&fn);
			free(mine);
			return (ARCHIVE_FATAL);
		}
		mine->filename_type = FNT_MBS;
		strcpy(mine->filename.m, fn.s);
		archive_string_free(&fn);
#endif
	}
	if (archive_read_append_callback_data(a, mine) != (ARCHIVE_OK))
		return (ARCHIVE_FATAL);
	archive_read_set_open_callback(a, file_open);
	archive_read_set_read_callback(a, file_read);
	archive_read_set_skip_callback(a, file_skip);
	archive_read_set_close_callback(a, file_close);
	archive_read_set_switch_callback(a, file_switch);
	archive_read_set_seek_callback(a, file_seek);

	return (archive_read_open1(a));
}