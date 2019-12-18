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
struct zip {int len_buf; int /*<<< orphan*/ * buf; int /*<<< orphan*/  crc32func; int /*<<< orphan*/  deflate_compression_level; int /*<<< orphan*/  requested_compression; } ;
struct TYPE_2__ {char* archive_format_name; int /*<<< orphan*/  archive_format; } ;
struct archive_write {char* format_name; TYPE_1__ archive; int /*<<< orphan*/  (* format_free ) (struct archive_write*) ;int /*<<< orphan*/  format_close; int /*<<< orphan*/  format_finish_entry; int /*<<< orphan*/  format_write_data; int /*<<< orphan*/  format_write_header; int /*<<< orphan*/  format_options; struct zip* format_data; } ;
struct archive {int dummy; } ;

/* Variables and functions */
 int ARCHIVE_FATAL ; 
 int /*<<< orphan*/  ARCHIVE_FORMAT_ZIP ; 
 int ARCHIVE_OK ; 
 int /*<<< orphan*/  ARCHIVE_STATE_NEW ; 
 int /*<<< orphan*/  ARCHIVE_WRITE_MAGIC ; 
 int /*<<< orphan*/  COMPRESSION_UNSPECIFIED ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  Z_DEFAULT_COMPRESSION ; 
 int /*<<< orphan*/  archive_check_magic (struct archive*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  archive_set_error (TYPE_1__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  archive_write_zip_close ; 
 int /*<<< orphan*/  archive_write_zip_data ; 
 int /*<<< orphan*/  archive_write_zip_finish_entry ; 
 int /*<<< orphan*/  archive_write_zip_free (struct archive_write*) ; 
 int /*<<< orphan*/  archive_write_zip_header ; 
 int /*<<< orphan*/  archive_write_zip_options ; 
 scalar_t__ calloc (int,int) ; 
 int /*<<< orphan*/  free (struct zip*) ; 
 int /*<<< orphan*/ * malloc (int) ; 
 int /*<<< orphan*/  real_crc32 ; 
 int /*<<< orphan*/  stub1 (struct archive_write*) ; 

int
archive_write_set_format_zip(struct archive *_a)
{
	struct archive_write *a = (struct archive_write *)_a;
	struct zip *zip;

	archive_check_magic(_a, ARCHIVE_WRITE_MAGIC,
	    ARCHIVE_STATE_NEW, "archive_write_set_format_zip");

	/* If another format was already registered, unregister it. */
	if (a->format_free != NULL)
		(a->format_free)(a);

	zip = (struct zip *) calloc(1, sizeof(*zip));
	if (zip == NULL) {
		archive_set_error(&a->archive, ENOMEM,
		    "Can't allocate zip data");
		return (ARCHIVE_FATAL);
	}

	/* "Unspecified" lets us choose the appropriate compression. */
	zip->requested_compression = COMPRESSION_UNSPECIFIED;
#ifdef HAVE_ZLIB_H
	zip->deflate_compression_level = Z_DEFAULT_COMPRESSION;
#endif
	zip->crc32func = real_crc32;

	/* A buffer used for both compression and encryption. */
	zip->len_buf = 65536;
	zip->buf = malloc(zip->len_buf);
	if (zip->buf == NULL) {
		free(zip);
		archive_set_error(&a->archive, ENOMEM,
		    "Can't allocate compression buffer");
		return (ARCHIVE_FATAL);
	}

	a->format_data = zip;
	a->format_name = "zip";
	a->format_options = archive_write_zip_options;
	a->format_write_header = archive_write_zip_header;
	a->format_write_data = archive_write_zip_data;
	a->format_finish_entry = archive_write_zip_finish_entry;
	a->format_close = archive_write_zip_close;
	a->format_free = archive_write_zip_free;
	a->archive.archive_format = ARCHIVE_FORMAT_ZIP;
	a->archive.archive_format_name = "ZIP";

	return (ARCHIVE_OK);
}