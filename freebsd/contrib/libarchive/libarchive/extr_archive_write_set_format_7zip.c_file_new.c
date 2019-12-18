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
struct file {unsigned int name_len; int dir; TYPE_1__* times; int /*<<< orphan*/  flg; int /*<<< orphan*/  size; int /*<<< orphan*/  mode; scalar_t__* utf16name; } ;
struct archive_write {int /*<<< orphan*/  archive; scalar_t__ format_data; } ;
struct archive_entry {int dummy; } ;
struct _7zip {int /*<<< orphan*/  sconv; } ;
struct TYPE_2__ {int /*<<< orphan*/  time_ns; int /*<<< orphan*/  time; } ;

/* Variables and functions */
 scalar_t__ AE_IFDIR ; 
 scalar_t__ AE_IFLNK ; 
 scalar_t__ AE_IFREG ; 
 scalar_t__ ARCHIVE_ERRNO_MISC ; 
 int ARCHIVE_FATAL ; 
 int ARCHIVE_OK ; 
 int ARCHIVE_WARN ; 
 size_t ATIME ; 
 int /*<<< orphan*/  ATIME_IS_SET ; 
 size_t CTIME ; 
 int /*<<< orphan*/  CTIME_IS_SET ; 
 scalar_t__ ENOMEM ; 
 size_t MTIME ; 
 int /*<<< orphan*/  MTIME_IS_SET ; 
 int /*<<< orphan*/  archive_entry_atime (struct archive_entry*) ; 
 scalar_t__ archive_entry_atime_is_set (struct archive_entry*) ; 
 int /*<<< orphan*/  archive_entry_atime_nsec (struct archive_entry*) ; 
 int /*<<< orphan*/  archive_entry_ctime (struct archive_entry*) ; 
 scalar_t__ archive_entry_ctime_is_set (struct archive_entry*) ; 
 int /*<<< orphan*/  archive_entry_ctime_nsec (struct archive_entry*) ; 
 scalar_t__ archive_entry_filetype (struct archive_entry*) ; 
 int /*<<< orphan*/  archive_entry_mode (struct archive_entry*) ; 
 int /*<<< orphan*/  archive_entry_mtime (struct archive_entry*) ; 
 scalar_t__ archive_entry_mtime_is_set (struct archive_entry*) ; 
 int /*<<< orphan*/  archive_entry_mtime_nsec (struct archive_entry*) ; 
 scalar_t__ archive_entry_pathname_l (struct archive_entry*,char const**,size_t*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  archive_entry_set_size (struct archive_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  archive_entry_size (struct archive_entry*) ; 
 int /*<<< orphan*/  archive_entry_symlink (struct archive_entry*) ; 
 int /*<<< orphan*/  archive_set_error (int /*<<< orphan*/ *,scalar_t__,char*) ; 
 struct file* calloc (int,int) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  free (struct file*) ; 
 scalar_t__* malloc (size_t) ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,char const*,size_t) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
file_new(struct archive_write *a, struct archive_entry *entry,
    struct file **newfile)
{
	struct _7zip *zip;
	struct file *file;
	const char *u16;
	size_t u16len;
	int ret = ARCHIVE_OK;

	zip = (struct _7zip *)a->format_data;
	*newfile = NULL;

	file = calloc(1, sizeof(*file));
	if (file == NULL) {
		archive_set_error(&a->archive, ENOMEM,
		    "Can't allocate memory");
		return (ARCHIVE_FATAL);
	}

	if (0 > archive_entry_pathname_l(entry, &u16, &u16len, zip->sconv)) {
		if (errno == ENOMEM) {
			free(file);
			archive_set_error(&a->archive, ENOMEM,
			    "Can't allocate memory for UTF-16LE");
			return (ARCHIVE_FATAL);
		}
		archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
		    "A filename cannot be converted to UTF-16LE;"
		    "You should disable making Joliet extension");
		ret = ARCHIVE_WARN;
	}
	file->utf16name = malloc(u16len + 2);
	if (file->utf16name == NULL) {
		free(file);
		archive_set_error(&a->archive, ENOMEM,
		    "Can't allocate memory for Name");
		return (ARCHIVE_FATAL);
	}
	memcpy(file->utf16name, u16, u16len);
	file->utf16name[u16len+0] = 0;
	file->utf16name[u16len+1] = 0;
	file->name_len = (unsigned)u16len;
	file->mode = archive_entry_mode(entry);
	if (archive_entry_filetype(entry) == AE_IFREG)
		file->size = archive_entry_size(entry);
	else
		archive_entry_set_size(entry, 0);
	if (archive_entry_filetype(entry) == AE_IFDIR)
		file->dir = 1;
	else if (archive_entry_filetype(entry) == AE_IFLNK)
		file->size = strlen(archive_entry_symlink(entry));
	if (archive_entry_mtime_is_set(entry)) {
		file->flg |= MTIME_IS_SET;
		file->times[MTIME].time = archive_entry_mtime(entry);
		file->times[MTIME].time_ns = archive_entry_mtime_nsec(entry);
	}
	if (archive_entry_atime_is_set(entry)) {
		file->flg |= ATIME_IS_SET;
		file->times[ATIME].time = archive_entry_atime(entry);
		file->times[ATIME].time_ns = archive_entry_atime_nsec(entry);
	}
	if (archive_entry_ctime_is_set(entry)) {
		file->flg |= CTIME_IS_SET;
		file->times[CTIME].time = archive_entry_ctime(entry);
		file->times[CTIME].time_ns = archive_entry_ctime_nsec(entry);
	}

	*newfile = file;
	return (ret);
}