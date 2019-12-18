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
struct bsdar {int argc; char** argv; int /*<<< orphan*/  v_obj; } ;
struct archive_entry {int dummy; } ;
struct archive {int dummy; } ;
struct ar_obj {char* maddr; size_t size; int fd; scalar_t__ ino; scalar_t__ dev; int /*<<< orphan*/  mtime; int /*<<< orphan*/  md; int /*<<< orphan*/  gid; int /*<<< orphan*/  uid; int /*<<< orphan*/ * name; } ;
typedef  scalar_t__ ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  AC (int /*<<< orphan*/ ) ; 
 int ARCHIVE_EOF ; 
 int ARCHIVE_FATAL ; 
 int ARCHIVE_RETRY ; 
 int ARCHIVE_WARN ; 
 int /*<<< orphan*/  DEF_BLKSZ ; 
 int /*<<< orphan*/  EX_DATAERR ; 
 int /*<<< orphan*/  EX_SOFTWARE ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct ar_obj*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  archive_entry_gid (struct archive_entry*) ; 
 int /*<<< orphan*/  archive_entry_mode (struct archive_entry*) ; 
 int /*<<< orphan*/  archive_entry_mtime (struct archive_entry*) ; 
 char* archive_entry_pathname (struct archive_entry*) ; 
 size_t archive_entry_size (struct archive_entry*) ; 
 int /*<<< orphan*/  archive_entry_uid (struct archive_entry*) ; 
 int /*<<< orphan*/  archive_errno (struct archive*) ; 
 int /*<<< orphan*/  archive_error_string (struct archive*) ; 
 int /*<<< orphan*/  archive_read_close (struct archive*) ; 
 scalar_t__ archive_read_data (struct archive*,char*,size_t) ; 
 int /*<<< orphan*/  archive_read_free (struct archive*) ; 
 struct archive* archive_read_new () ; 
 int archive_read_next_header (struct archive*,struct archive_entry**) ; 
 int /*<<< orphan*/  archive_read_open_filename (struct archive*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  archive_read_support_format_ar (struct archive*) ; 
 char* basename (char*) ; 
 int /*<<< orphan*/  bsdar_errc (struct bsdar*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  bsdar_warnc (struct bsdar*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  free (char*) ; 
 void* malloc (int) ; 
 int /*<<< orphan*/  objs ; 
 scalar_t__ strcmp (char const*,char const*) ; 
 int /*<<< orphan*/ * strdup (char const*) ; 

__attribute__((used)) static void
read_objs(struct bsdar *bsdar, const char *archive, int checkargv)
{
	struct archive		 *a;
	struct archive_entry	 *entry;
	struct ar_obj		 *obj;
	const char		 *name;
	const char		 *bname;
	char			 *buff;
	char			**av;
	size_t			  size;
	int			  i, r, find;

	if ((a = archive_read_new()) == NULL)
		bsdar_errc(bsdar, EX_SOFTWARE, 0, "archive_read_new failed");
	archive_read_support_format_ar(a);
	AC(archive_read_open_filename(a, archive, DEF_BLKSZ));
	for (;;) {
		r = archive_read_next_header(a, &entry);
		if (r == ARCHIVE_FATAL)
			bsdar_errc(bsdar, EX_DATAERR, archive_errno(a), "%s",
			    archive_error_string(a));
		if (r == ARCHIVE_EOF)
			break;
		if (r == ARCHIVE_WARN || r == ARCHIVE_RETRY)
			bsdar_warnc(bsdar, archive_errno(a), "%s",
			    archive_error_string(a));
		if (r == ARCHIVE_RETRY) {
			bsdar_warnc(bsdar, 0, "Retrying...");
			continue;
		}

		name = archive_entry_pathname(entry);

		/*
		 * skip pseudo members.
		 */
		if (strcmp(name, "/") == 0 || strcmp(name, "//") == 0)
			continue;

		/*
		 * If checkargv is set, only read those members specified
		 * in argv.
		 */
		if (checkargv && bsdar->argc > 0) {
			find = 0;
			for(i = 0; i < bsdar->argc; i++) {
				av = &bsdar->argv[i];
				if (*av == NULL)
					continue;
				if ((bname = basename(*av)) == NULL)
					bsdar_errc(bsdar, EX_SOFTWARE, errno,
					    "basename failed");
				if (strcmp(bname, name) != 0)
					continue;

				*av = NULL;
				find = 1;
				break;
			}
			if (!find)
				continue;
		}

		size = archive_entry_size(entry);

		if (size > 0) {
			if ((buff = malloc(size)) == NULL)
				bsdar_errc(bsdar, EX_SOFTWARE, errno,
				    "malloc failed");
			if (archive_read_data(a, buff, size) != (ssize_t)size) {
				bsdar_warnc(bsdar, archive_errno(a), "%s",
				    archive_error_string(a));
				free(buff);
				continue;
			}
		} else
			buff = NULL;

		obj = malloc(sizeof(struct ar_obj));
		if (obj == NULL)
			bsdar_errc(bsdar, EX_SOFTWARE, errno, "malloc failed");
		obj->maddr = buff;
		if ((obj->name = strdup(name)) == NULL)
			bsdar_errc(bsdar, EX_SOFTWARE, errno, "strdup failed");
		obj->size = size;
		obj->uid = archive_entry_uid(entry);
		obj->gid = archive_entry_gid(entry);
		obj->md = archive_entry_mode(entry);
		obj->mtime = archive_entry_mtime(entry);
		obj->dev = 0;
		obj->ino = 0;

		/*
		 * Objects from archive have obj->fd set to -1,
		 * for the ease of cleaning up.
		 */
		obj->fd = -1;
		TAILQ_INSERT_TAIL(&bsdar->v_obj, obj, objs);
	}
	AC(archive_read_close(a));
	AC(archive_read_free(a));
}