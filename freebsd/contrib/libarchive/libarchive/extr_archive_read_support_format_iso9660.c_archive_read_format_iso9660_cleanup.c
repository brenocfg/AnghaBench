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
struct TYPE_7__ {int /*<<< orphan*/  stream; scalar_t__ stream_valid; struct iso9660* block_pointers; struct iso9660* uncompressed_buffer; } ;
struct TYPE_6__ {struct iso9660* files; } ;
struct TYPE_5__ {struct iso9660* reqs; } ;
struct iso9660 {struct iso9660* utf16be_previous_path; struct iso9660* utf16be_path; TYPE_3__ entry_zisofs; TYPE_2__ pending_files; int /*<<< orphan*/  previous_pathname; int /*<<< orphan*/  pathname; TYPE_1__ read_ce_req; } ;
struct archive_read {TYPE_4__* format; int /*<<< orphan*/  archive; } ;
struct TYPE_8__ {int /*<<< orphan*/ * data; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARCHIVE_ERRNO_MISC ; 
 int ARCHIVE_FATAL ; 
 int ARCHIVE_OK ; 
 scalar_t__ Z_OK ; 
 int /*<<< orphan*/  archive_set_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  archive_string_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (struct iso9660*) ; 
 scalar_t__ inflateEnd (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  release_files (struct iso9660*) ; 

__attribute__((used)) static int
archive_read_format_iso9660_cleanup(struct archive_read *a)
{
	struct iso9660 *iso9660;
	int r = ARCHIVE_OK;

	iso9660 = (struct iso9660 *)(a->format->data);
	release_files(iso9660);
	free(iso9660->read_ce_req.reqs);
	archive_string_free(&iso9660->pathname);
	archive_string_free(&iso9660->previous_pathname);
	free(iso9660->pending_files.files);
#ifdef HAVE_ZLIB_H
	free(iso9660->entry_zisofs.uncompressed_buffer);
	free(iso9660->entry_zisofs.block_pointers);
	if (iso9660->entry_zisofs.stream_valid) {
		if (inflateEnd(&iso9660->entry_zisofs.stream) != Z_OK) {
			archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
			    "Failed to clean up zlib decompressor");
			r = ARCHIVE_FATAL;
		}
	}
#endif
	free(iso9660->utf16be_path);
	free(iso9660->utf16be_previous_path);
	free(iso9660);
	(a->format->data) = NULL;
	return (r);
}