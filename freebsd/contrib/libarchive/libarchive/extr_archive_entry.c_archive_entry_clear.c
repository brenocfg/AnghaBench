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
struct archive_entry {int /*<<< orphan*/  ae_symlink_type; int /*<<< orphan*/  stat; int /*<<< orphan*/  acl; int /*<<< orphan*/  ae_uname; int /*<<< orphan*/  ae_symlink; int /*<<< orphan*/  ae_sourcepath; int /*<<< orphan*/  ae_pathname; int /*<<< orphan*/  ae_hardlink; int /*<<< orphan*/  ae_gname; int /*<<< orphan*/  ae_fflags_text; } ;

/* Variables and functions */
 int /*<<< orphan*/  AE_SYMLINK_TYPE_UNDEFINED ; 
 int /*<<< orphan*/  archive_acl_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  archive_entry_copy_mac_metadata (struct archive_entry*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  archive_entry_sparse_clear (struct archive_entry*) ; 
 int /*<<< orphan*/  archive_entry_xattr_clear (struct archive_entry*) ; 
 int /*<<< orphan*/  archive_mstring_clean (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct archive_entry*,int /*<<< orphan*/ ,int) ; 

struct archive_entry *
archive_entry_clear(struct archive_entry *entry)
{
	if (entry == NULL)
		return (NULL);
	archive_mstring_clean(&entry->ae_fflags_text);
	archive_mstring_clean(&entry->ae_gname);
	archive_mstring_clean(&entry->ae_hardlink);
	archive_mstring_clean(&entry->ae_pathname);
	archive_mstring_clean(&entry->ae_sourcepath);
	archive_mstring_clean(&entry->ae_symlink);
	archive_mstring_clean(&entry->ae_uname);
	archive_entry_copy_mac_metadata(entry, NULL, 0);
	archive_acl_clear(&entry->acl);
	archive_entry_xattr_clear(entry);
	archive_entry_sparse_clear(entry);
	free(entry->stat);
	entry->ae_symlink_type = AE_SYMLINK_TYPE_UNDEFINED;
	memset(entry, 0, sizeof(*entry));
	return entry;
}