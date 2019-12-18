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
typedef  int /*<<< orphan*/  wchar_t ;
struct archive_string {int /*<<< orphan*/  s; } ;
struct TYPE_3__ {int /*<<< orphan*/  state; } ;
struct archive_read_disk {TYPE_1__ archive; } ;
struct archive {int dummy; } ;

/* Variables and functions */
 scalar_t__ ARCHIVE_ERRNO_MISC ; 
 int ARCHIVE_FATAL ; 
 int /*<<< orphan*/  ARCHIVE_READ_DISK_MAGIC ; 
 int ARCHIVE_STATE_CLOSED ; 
 int /*<<< orphan*/  ARCHIVE_STATE_FATAL ; 
 int ARCHIVE_STATE_NEW ; 
 scalar_t__ ENOMEM ; 
 int _archive_read_disk_open (struct archive*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  archive_check_magic (struct archive*,int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  archive_clear_error (TYPE_1__*) ; 
 int /*<<< orphan*/  archive_set_error (TYPE_1__*,scalar_t__,char*) ; 
 scalar_t__ archive_string_append_from_wcs (struct archive_string*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  archive_string_free (struct archive_string*) ; 
 int /*<<< orphan*/  archive_string_init (struct archive_string*) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  wcslen (int /*<<< orphan*/  const*) ; 

int
archive_read_disk_open_w(struct archive *_a, const wchar_t *pathname)
{
	struct archive_read_disk *a = (struct archive_read_disk *)_a;
	struct archive_string path;
	int ret;

	archive_check_magic(_a, ARCHIVE_READ_DISK_MAGIC,
	    ARCHIVE_STATE_NEW | ARCHIVE_STATE_CLOSED,
	    "archive_read_disk_open_w");
	archive_clear_error(&a->archive);

	/* Make a char string from a wchar_t string. */
	archive_string_init(&path);
	if (archive_string_append_from_wcs(&path, pathname,
	    wcslen(pathname)) != 0) {
		if (errno == ENOMEM)
			archive_set_error(&a->archive, ENOMEM,
			    "Can't allocate memory");
		else
			archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
			    "Can't convert a path to a char string");
		a->archive.state = ARCHIVE_STATE_FATAL;
		ret = ARCHIVE_FATAL;
	} else
		ret = _archive_read_disk_open(_a, path.s);

	archive_string_free(&path);
	return (ret);
}