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
struct archive_read_disk {scalar_t__ (* tree_enter_working_dir ) (int /*<<< orphan*/ *) ;int (* open_on_current_dir ) (int /*<<< orphan*/ *,char const*,int) ;int /*<<< orphan*/ * tree; scalar_t__ follow_symlinks; int /*<<< orphan*/  archive; } ;
struct archive_entry {int dummy; } ;

/* Variables and functions */
 scalar_t__ AE_IFLNK ; 
 int /*<<< orphan*/  ARCHIVE_ERRNO_MISC ; 
 int O_NONBLOCK ; 
 int O_RDONLY ; 
 scalar_t__ archive_entry_filetype (struct archive_entry*) ; 
 char* archive_entry_pathname (struct archive_entry*) ; 
 char* archive_entry_sourcepath (struct archive_entry*) ; 
 int /*<<< orphan*/  archive_set_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ *) ; 
 int stub2 (int /*<<< orphan*/ *,char const*,int) ; 

const char *
archive_read_disk_entry_setup_path(struct archive_read_disk *a,
    struct archive_entry *entry, int *fd)
{
	const char *path;

	path = archive_entry_sourcepath(entry);

	if (path == NULL || (a->tree != NULL &&
	    a->tree_enter_working_dir(a->tree) != 0))
		path = archive_entry_pathname(entry);
	if (path == NULL) {
		archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
		   "Couldn't determine path");
	} else if (fd != NULL && *fd < 0 && a->tree != NULL &&
	    (a->follow_symlinks || archive_entry_filetype(entry) != AE_IFLNK)) {
		*fd = a->open_on_current_dir(a->tree, path,
		    O_RDONLY | O_NONBLOCK);
	}
	return (path);
}