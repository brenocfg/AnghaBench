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
struct isofile {int /*<<< orphan*/  entry; } ;
struct isoent {int dir; int virtual; } ;
struct iso9660 {int dummy; } ;
struct archive_write {int dummy; } ;

/* Variables and functions */
 int AE_IFDIR ; 
 scalar_t__ ARCHIVE_WARN ; 
 int /*<<< orphan*/  archive_entry_set_gid (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  archive_entry_set_mode (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  archive_entry_set_nlink (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  archive_entry_set_pathname (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  archive_entry_set_uid (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  archive_entry_unset_atime (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  archive_entry_unset_ctime (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  archive_entry_unset_mtime (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  getgid () ; 
 int /*<<< orphan*/  getuid () ; 
 struct isoent* isoent_new (struct isofile*) ; 
 int /*<<< orphan*/  isofile_add_entry (struct iso9660*,struct isofile*) ; 
 int /*<<< orphan*/  isofile_free (struct isofile*) ; 
 scalar_t__ isofile_gen_utility_names (struct archive_write*,struct isofile*) ; 
 struct isofile* isofile_new (struct archive_write*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct isoent *
isoent_create_virtual_dir(struct archive_write *a, struct iso9660 *iso9660, const char *pathname)
{
	struct isofile *file;
	struct isoent *isoent;

	file = isofile_new(a, NULL);
	if (file == NULL)
		return (NULL);
	archive_entry_set_pathname(file->entry, pathname);
	archive_entry_unset_mtime(file->entry);
	archive_entry_unset_atime(file->entry);
	archive_entry_unset_ctime(file->entry);
	archive_entry_set_uid(file->entry, getuid());
	archive_entry_set_gid(file->entry, getgid());
	archive_entry_set_mode(file->entry, 0555 | AE_IFDIR);
	archive_entry_set_nlink(file->entry, 2);
	if (isofile_gen_utility_names(a, file) < ARCHIVE_WARN) {
		isofile_free(file);
		return (NULL);
	}
	isofile_add_entry(iso9660, file);

	isoent = isoent_new(file);
	if (isoent == NULL)
		return (NULL);
	isoent->dir = 1;
	isoent->virtual = 1;

	return (isoent);
}