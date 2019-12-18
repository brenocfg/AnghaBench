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
struct cpio {int return_value; char const* destdir; size_t pass_destpath_alloc; char* pass_destpath; int /*<<< orphan*/ * linkresolver; scalar_t__ option_rename; int /*<<< orphan*/  gname_override; int /*<<< orphan*/  gid_override; int /*<<< orphan*/  uname_override; int /*<<< orphan*/  uid_override; int /*<<< orphan*/  archive_read_disk; } ;
struct archive_entry {int dummy; } ;

/* Variables and functions */
 scalar_t__ AE_IFDIR ; 
 int ARCHIVE_FAILED ; 
 int ARCHIVE_OK ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  archive_entry_copy_pathname (struct archive_entry*,char const*) ; 
 int /*<<< orphan*/  archive_entry_copy_sourcepath (struct archive_entry*,char const*) ; 
 scalar_t__ archive_entry_filetype (struct archive_entry*) ; 
 int /*<<< orphan*/  archive_entry_free (struct archive_entry*) ; 
 int /*<<< orphan*/  archive_entry_linkify (int /*<<< orphan*/ *,struct archive_entry**,struct archive_entry**) ; 
 struct archive_entry* archive_entry_new () ; 
 int /*<<< orphan*/  archive_entry_set_gid (struct archive_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  archive_entry_set_gname (struct archive_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  archive_entry_set_uid (struct archive_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  archive_entry_set_uname (struct archive_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  archive_error_string (int /*<<< orphan*/ ) ; 
 int archive_read_disk_entry_from_file (int /*<<< orphan*/ ,struct archive_entry*,int,int /*<<< orphan*/ *) ; 
 char* cpio_rename (char const*) ; 
 int entry_to_archive (struct cpio*,struct archive_entry*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  lafe_errc (int,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  lafe_warnc (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 char* malloc (int) ; 
 int /*<<< orphan*/  remove_leading_slash (char const*) ; 
 int /*<<< orphan*/  strcat (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 int strlen (char const*) ; 

__attribute__((used)) static int
file_to_archive(struct cpio *cpio, const char *srcpath)
{
	const char *destpath;
	struct archive_entry *entry, *spare;
	size_t len;
	int r;

	/*
	 * Create an archive_entry describing the source file.
	 *
	 */
	entry = archive_entry_new();
	if (entry == NULL)
		lafe_errc(1, 0, "Couldn't allocate entry");
	archive_entry_copy_sourcepath(entry, srcpath);
	r = archive_read_disk_entry_from_file(cpio->archive_read_disk,
	    entry, -1, NULL);
	if (r < ARCHIVE_FAILED)
		lafe_errc(1, 0, "%s",
		    archive_error_string(cpio->archive_read_disk));
	if (r < ARCHIVE_OK)
		lafe_warnc(0, "%s",
		    archive_error_string(cpio->archive_read_disk));
	if (r <= ARCHIVE_FAILED) {
		archive_entry_free(entry);
		cpio->return_value = 1;
		return (r);
	}

	if (cpio->uid_override >= 0) {
		archive_entry_set_uid(entry, cpio->uid_override);
		archive_entry_set_uname(entry, cpio->uname_override);
	}
	if (cpio->gid_override >= 0) {
		archive_entry_set_gid(entry, cpio->gid_override);
		archive_entry_set_gname(entry, cpio->gname_override);
	}

	/*
	 * Generate a destination path for this entry.
	 * "destination path" is the name to which it will be copied in
	 * pass mode or the name that will go into the archive in
	 * output mode.
	 */
	destpath = srcpath;
	if (cpio->destdir) {
		len = strlen(cpio->destdir) + strlen(srcpath) + 8;
		if (len >= cpio->pass_destpath_alloc) {
			while (len >= cpio->pass_destpath_alloc) {
				cpio->pass_destpath_alloc += 512;
				cpio->pass_destpath_alloc *= 2;
			}
			free(cpio->pass_destpath);
			cpio->pass_destpath = malloc(cpio->pass_destpath_alloc);
			if (cpio->pass_destpath == NULL)
				lafe_errc(1, ENOMEM,
				    "Can't allocate path buffer");
		}
		strcpy(cpio->pass_destpath, cpio->destdir);
		strcat(cpio->pass_destpath, remove_leading_slash(srcpath));
		destpath = cpio->pass_destpath;
	}
	if (cpio->option_rename)
		destpath = cpio_rename(destpath);
	if (destpath == NULL) {
		archive_entry_free(entry);
		return (0);
	}
	archive_entry_copy_pathname(entry, destpath);

	/*
	 * If we're trying to preserve hardlinks, match them here.
	 */
	spare = NULL;
	if (cpio->linkresolver != NULL
	    && archive_entry_filetype(entry) != AE_IFDIR) {
		archive_entry_linkify(cpio->linkresolver, &entry, &spare);
	}

	if (entry != NULL) {
		r = entry_to_archive(cpio, entry);
		archive_entry_free(entry);
		if (spare != NULL) {
			if (r == 0)
				r = entry_to_archive(cpio, spare);
			archive_entry_free(spare);
		}
	}
	return (r);
}