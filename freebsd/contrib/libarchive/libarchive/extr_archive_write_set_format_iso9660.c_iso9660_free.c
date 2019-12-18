#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  id; int /*<<< orphan*/  boot_filename; int /*<<< orphan*/  catalog_filename; } ;
struct TYPE_7__ {int max_depth; struct iso9660* pathtbl; int /*<<< orphan*/  rootent; } ;
struct TYPE_6__ {scalar_t__ joliet; } ;
struct TYPE_5__ {int max_depth; struct iso9660* pathtbl; int /*<<< orphan*/  rootent; } ;
struct iso9660 {scalar_t__ temp_fd; int /*<<< orphan*/  mbs; int /*<<< orphan*/  utf16be; TYPE_4__ el_torito; int /*<<< orphan*/  bibliographic_file_identifier; int /*<<< orphan*/  abstract_file_identifier; int /*<<< orphan*/  copyright_file_identifier; int /*<<< orphan*/  application_identifier; int /*<<< orphan*/  data_preparer_identifier; int /*<<< orphan*/  publisher_identifier; int /*<<< orphan*/  volume_identifier; int /*<<< orphan*/  cur_dirstr; TYPE_3__ joliet; struct iso9660* sorted; TYPE_2__ opt; TYPE_1__ primary; } ;
struct archive_write {struct iso9660* format_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  archive_string_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  close (scalar_t__) ; 
 int /*<<< orphan*/  free (struct iso9660*) ; 
 int /*<<< orphan*/  isoent_free_all (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isofile_free_all_entries (struct iso9660*) ; 
 int /*<<< orphan*/  isofile_free_hardlinks (struct iso9660*) ; 
 int zisofs_free (struct archive_write*) ; 

__attribute__((used)) static int
iso9660_free(struct archive_write *a)
{
	struct iso9660 *iso9660;
	int i, ret;

	iso9660 = a->format_data;

	/* Close the temporary file. */
	if (iso9660->temp_fd >= 0)
		close(iso9660->temp_fd);

	/* Free some stuff for zisofs operations. */
	ret = zisofs_free(a);

	/* Remove directory entries in tree which includes file entries. */
	isoent_free_all(iso9660->primary.rootent);
	for (i = 0; i < iso9660->primary.max_depth; i++)
		free(iso9660->primary.pathtbl[i].sorted);
	free(iso9660->primary.pathtbl);

	if (iso9660->opt.joliet) {
		isoent_free_all(iso9660->joliet.rootent);
		for (i = 0; i < iso9660->joliet.max_depth; i++)
			free(iso9660->joliet.pathtbl[i].sorted);
		free(iso9660->joliet.pathtbl);
	}

	/* Remove isofile entries. */
	isofile_free_all_entries(iso9660);
	isofile_free_hardlinks(iso9660);

	archive_string_free(&(iso9660->cur_dirstr));
	archive_string_free(&(iso9660->volume_identifier));
	archive_string_free(&(iso9660->publisher_identifier));
	archive_string_free(&(iso9660->data_preparer_identifier));
	archive_string_free(&(iso9660->application_identifier));
	archive_string_free(&(iso9660->copyright_file_identifier));
	archive_string_free(&(iso9660->abstract_file_identifier));
	archive_string_free(&(iso9660->bibliographic_file_identifier));
	archive_string_free(&(iso9660->el_torito.catalog_filename));
	archive_string_free(&(iso9660->el_torito.boot_filename));
	archive_string_free(&(iso9660->el_torito.id));
	archive_string_free(&(iso9660->utf16be));
	archive_string_free(&(iso9660->mbs));

	free(iso9660);
	a->format_data = NULL;

	return (ret);
}