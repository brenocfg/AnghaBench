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
struct bsdtar {int flags; int return_value; int /*<<< orphan*/  matching; int /*<<< orphan*/  extract_flags; } ;
struct archive {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 int OPTFLAG_NUMERIC_OWNER ; 
 struct archive* archive_write_disk_new () ; 
 int /*<<< orphan*/  archive_write_disk_set_options (struct archive*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  archive_write_disk_set_standard_lookup (struct archive*) ; 
 int /*<<< orphan*/  archive_write_free (struct archive*) ; 
 int /*<<< orphan*/  lafe_errc (int,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  read_archive (struct bsdtar*,char,struct archive*) ; 
 scalar_t__ unmatched_inclusions_warn (int /*<<< orphan*/ ,char*) ; 

void
tar_mode_x(struct bsdtar *bsdtar)
{
	struct archive *writer;

	writer = archive_write_disk_new();
	if (writer == NULL)
		lafe_errc(1, ENOMEM, "Cannot allocate disk writer object");
	if ((bsdtar->flags & OPTFLAG_NUMERIC_OWNER) == 0)
		archive_write_disk_set_standard_lookup(writer);
	archive_write_disk_set_options(writer, bsdtar->extract_flags);

	read_archive(bsdtar, 'x', writer);

	if (unmatched_inclusions_warn(bsdtar->matching,
	    "Not found in archive") != 0)
		bsdtar->return_value = 1;
	archive_write_free(writer);
}