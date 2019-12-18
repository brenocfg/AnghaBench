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
struct isofile {int /*<<< orphan*/  content; int /*<<< orphan*/ * cur_content; int /*<<< orphan*/  symlink; int /*<<< orphan*/  basename_utf16; int /*<<< orphan*/  basename; int /*<<< orphan*/  parentdir; int /*<<< orphan*/ * entry; } ;
struct archive_write {int /*<<< orphan*/  archive; } ;
struct archive_entry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/ * archive_entry_clone (struct archive_entry*) ; 
 int /*<<< orphan*/ * archive_entry_new2 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  archive_string_init (int /*<<< orphan*/ *) ; 
 struct isofile* calloc (int,int) ; 
 int /*<<< orphan*/  free (struct isofile*) ; 

__attribute__((used)) static struct isofile *
isofile_new(struct archive_write *a, struct archive_entry *entry)
{
	struct isofile *file;

	file = calloc(1, sizeof(*file));
	if (file == NULL)
		return (NULL);

	if (entry != NULL)
		file->entry = archive_entry_clone(entry);
	else
		file->entry = archive_entry_new2(&a->archive);
	if (file->entry == NULL) {
		free(file);
		return (NULL);
	}
	archive_string_init(&(file->parentdir));
	archive_string_init(&(file->basename));
	archive_string_init(&(file->basename_utf16));
	archive_string_init(&(file->symlink));
	file->cur_content = &(file->content);

	return (file);
}