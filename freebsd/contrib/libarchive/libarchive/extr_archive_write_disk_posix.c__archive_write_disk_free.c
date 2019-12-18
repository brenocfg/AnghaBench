#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ magic; int /*<<< orphan*/  error_string; } ;
struct archive_write_disk {TYPE_1__ archive; int /*<<< orphan*/  stream; scalar_t__ stream_valid; struct archive_write_disk* uncompressed_buffer; struct archive_write_disk* compressed_buffer; struct archive_write_disk* resource_fork; struct archive_write_disk* decmpfs_header_p; int /*<<< orphan*/  path_safe; int /*<<< orphan*/  _name_data; int /*<<< orphan*/  entry; } ;
struct archive {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARCHIVE_ERRNO_MISC ; 
 int ARCHIVE_FATAL ; 
 int ARCHIVE_OK ; 
 int ARCHIVE_STATE_ANY ; 
 int ARCHIVE_STATE_FATAL ; 
 int /*<<< orphan*/  ARCHIVE_WRITE_DISK_MAGIC ; 
#define  Z_OK 128 
 int /*<<< orphan*/  __archive_clean (TYPE_1__*) ; 
 int _archive_write_disk_close (TYPE_1__*) ; 
 int /*<<< orphan*/  archive_check_magic (struct archive*,int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  archive_entry_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  archive_set_error (TYPE_1__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  archive_string_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  archive_write_disk_set_group_lookup (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  archive_write_disk_set_user_lookup (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int deflateEnd (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (struct archive_write_disk*) ; 

__attribute__((used)) static int
_archive_write_disk_free(struct archive *_a)
{
	struct archive_write_disk *a;
	int ret;
	if (_a == NULL)
		return (ARCHIVE_OK);
	archive_check_magic(_a, ARCHIVE_WRITE_DISK_MAGIC,
	    ARCHIVE_STATE_ANY | ARCHIVE_STATE_FATAL, "archive_write_disk_free");
	a = (struct archive_write_disk *)_a;
	ret = _archive_write_disk_close(&a->archive);
	archive_write_disk_set_group_lookup(&a->archive, NULL, NULL, NULL);
	archive_write_disk_set_user_lookup(&a->archive, NULL, NULL, NULL);
	archive_entry_free(a->entry);
	archive_string_free(&a->_name_data);
	archive_string_free(&a->archive.error_string);
	archive_string_free(&a->path_safe);
	a->archive.magic = 0;
	__archive_clean(&a->archive);
	free(a->decmpfs_header_p);
	free(a->resource_fork);
	free(a->compressed_buffer);
	free(a->uncompressed_buffer);
#if defined(__APPLE__) && defined(UF_COMPRESSED) && defined(HAVE_SYS_XATTR_H)\
	&& defined(HAVE_ZLIB_H)
	if (a->stream_valid) {
		switch (deflateEnd(&a->stream)) {
		case Z_OK:
			break;
		default:
			archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
			    "Failed to clean up compressor");
			ret = ARCHIVE_FATAL;
			break;
		}
	}
#endif
	free(a);
	return (ret);
}