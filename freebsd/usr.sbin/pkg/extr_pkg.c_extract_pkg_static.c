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
struct archive_entry {int dummy; } ;
struct archive {int dummy; } ;

/* Variables and functions */
 int ARCHIVE_EXTRACT_ACL ; 
 int ARCHIVE_EXTRACT_FFLAGS ; 
 int ARCHIVE_EXTRACT_OWNER ; 
 int ARCHIVE_EXTRACT_PERM ; 
 int ARCHIVE_EXTRACT_TIME ; 
 int ARCHIVE_EXTRACT_XATTR ; 
 int ARCHIVE_OK ; 
 int /*<<< orphan*/  archive_entry_pathname (struct archive_entry*) ; 
 int /*<<< orphan*/  archive_error_string (struct archive*) ; 
 int archive_read_extract (struct archive*,struct archive_entry*,int) ; 
 int /*<<< orphan*/  archive_read_free (struct archive*) ; 
 struct archive* archive_read_new () ; 
 int archive_read_next_header (struct archive*,struct archive_entry**) ; 
 int archive_read_open_fd (struct archive*,int,int) ; 
 int /*<<< orphan*/  archive_read_support_filter_all (struct archive*) ; 
 int /*<<< orphan*/  archive_read_support_format_tar (struct archive*) ; 
 int lseek (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  strlcpy (char*,int /*<<< orphan*/ ,int) ; 
 char* strrchr (int /*<<< orphan*/ ,char) ; 
 int /*<<< orphan*/  warn (char*) ; 
 int /*<<< orphan*/  warnx (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
extract_pkg_static(int fd, char *p, int sz)
{
	struct archive *a;
	struct archive_entry *ae;
	char *end;
	int ret, r;

	ret = -1;
	a = archive_read_new();
	if (a == NULL) {
		warn("archive_read_new");
		return (ret);
	}
	archive_read_support_filter_all(a);
	archive_read_support_format_tar(a);

	if (lseek(fd, 0, 0) == -1) {
		warn("lseek");
		goto cleanup;
	}

	if (archive_read_open_fd(a, fd, 4096) != ARCHIVE_OK) {
		warnx("archive_read_open_fd: %s", archive_error_string(a));
		goto cleanup;
	}

	ae = NULL;
	while ((r = archive_read_next_header(a, &ae)) == ARCHIVE_OK) {
		end = strrchr(archive_entry_pathname(ae), '/');
		if (end == NULL)
			continue;

		if (strcmp(end, "/pkg-static") == 0) {
			r = archive_read_extract(a, ae,
			    ARCHIVE_EXTRACT_OWNER | ARCHIVE_EXTRACT_PERM |
			    ARCHIVE_EXTRACT_TIME | ARCHIVE_EXTRACT_ACL |
			    ARCHIVE_EXTRACT_FFLAGS | ARCHIVE_EXTRACT_XATTR);
			strlcpy(p, archive_entry_pathname(ae), sz);
			break;
		}
	}

	if (r == ARCHIVE_OK)
		ret = 0;
	else
		warnx("failed to extract pkg-static: %s",
		    archive_error_string(a));

cleanup:
	archive_read_free(a);
	return (ret);

}