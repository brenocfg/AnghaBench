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
struct lafe_line_reader {int dummy; } ;
struct cpio {int compress; int add_filter; int /*<<< orphan*/  linkresolver; int /*<<< orphan*/ * archive; int /*<<< orphan*/  quiet; scalar_t__ dot; int /*<<< orphan*/  option_null; int /*<<< orphan*/  filename; int /*<<< orphan*/ * passphrase; int /*<<< orphan*/  bytes_per_block; int /*<<< orphan*/  format; int /*<<< orphan*/ * archive_read_disk; scalar_t__ option_follow_links; scalar_t__ option_append; } ;
struct archive_entry {int dummy; } ;
typedef  int int64_t ;

/* Variables and functions */
 int ARCHIVE_OK ; 
 int ARCHIVE_WARN ; 
#define  OPTION_B64ENCODE 135 
#define  OPTION_GRZIP 134 
#define  OPTION_LRZIP 133 
#define  OPTION_LZ4 132 
#define  OPTION_LZMA 131 
#define  OPTION_LZOP 130 
#define  OPTION_UUENCODE 129 
#define  OPTION_ZSTD 128 
 int /*<<< orphan*/  archive_entry_free (struct archive_entry*) ; 
 int /*<<< orphan*/  archive_entry_linkify (int /*<<< orphan*/ ,struct archive_entry**,struct archive_entry**) ; 
 int /*<<< orphan*/  archive_entry_linkresolver_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  archive_entry_linkresolver_new () ; 
 int /*<<< orphan*/  archive_entry_linkresolver_set_strategy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  archive_error_string (int /*<<< orphan*/ *) ; 
 int archive_filter_bytes (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  archive_format (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * archive_read_disk_new () ; 
 int /*<<< orphan*/  archive_read_disk_set_standard_lookup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  archive_read_disk_set_symlink_logical (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  archive_read_disk_set_symlink_physical (int /*<<< orphan*/ *) ; 
 int archive_write_add_filter_b64encode (int /*<<< orphan*/ *) ; 
 int archive_write_add_filter_bzip2 (int /*<<< orphan*/ *) ; 
 int archive_write_add_filter_compress (int /*<<< orphan*/ *) ; 
 int archive_write_add_filter_grzip (int /*<<< orphan*/ *) ; 
 int archive_write_add_filter_gzip (int /*<<< orphan*/ *) ; 
 int archive_write_add_filter_lrzip (int /*<<< orphan*/ *) ; 
 int archive_write_add_filter_lz4 (int /*<<< orphan*/ *) ; 
 int archive_write_add_filter_lzma (int /*<<< orphan*/ *) ; 
 int archive_write_add_filter_lzop (int /*<<< orphan*/ *) ; 
 int archive_write_add_filter_none (int /*<<< orphan*/ *) ; 
 int archive_write_add_filter_uuencode (int /*<<< orphan*/ *) ; 
 int archive_write_add_filter_xz (int /*<<< orphan*/ *) ; 
 int archive_write_add_filter_zstd (int /*<<< orphan*/ *) ; 
 int archive_write_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  archive_write_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * archive_write_new () ; 
 int archive_write_open_filename (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  archive_write_set_bytes_per_block (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int archive_write_set_format_by_name (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int archive_write_set_passphrase (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int archive_write_set_passphrase_callback (int /*<<< orphan*/ *,struct cpio*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  entry_to_archive (struct cpio*,struct archive_entry*) ; 
 int /*<<< orphan*/  file_to_archive (struct cpio*,char const*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  lafe_errc (int,int /*<<< orphan*/ ,char*,...) ; 
 struct lafe_line_reader* lafe_line_reader (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lafe_line_reader_free (struct lafe_line_reader*) ; 
 char* lafe_line_reader_next (struct lafe_line_reader*) ; 
 int /*<<< orphan*/  passphrase_callback ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void
mode_out(struct cpio *cpio)
{
	struct archive_entry *entry, *spare;
	struct lafe_line_reader *lr;
	const char *p;
	int r;

	if (cpio->option_append)
		lafe_errc(1, 0, "Append mode not yet supported.");

	cpio->archive_read_disk = archive_read_disk_new();
	if (cpio->archive_read_disk == NULL)
		lafe_errc(1, 0, "Failed to allocate archive object");
	if (cpio->option_follow_links)
		archive_read_disk_set_symlink_logical(cpio->archive_read_disk);
	else
		archive_read_disk_set_symlink_physical(cpio->archive_read_disk);
	archive_read_disk_set_standard_lookup(cpio->archive_read_disk);

	cpio->archive = archive_write_new();
	if (cpio->archive == NULL)
		lafe_errc(1, 0, "Failed to allocate archive object");
	switch (cpio->compress) {
	case OPTION_GRZIP:
		r = archive_write_add_filter_grzip(cpio->archive);
		break;
	case 'J':
		r = archive_write_add_filter_xz(cpio->archive);
		break;
	case OPTION_LRZIP:
		r = archive_write_add_filter_lrzip(cpio->archive);
		break;
	case OPTION_LZ4:
		r = archive_write_add_filter_lz4(cpio->archive);
		break;
	case OPTION_LZMA:
		r = archive_write_add_filter_lzma(cpio->archive);
		break;
	case OPTION_LZOP:
		r = archive_write_add_filter_lzop(cpio->archive);
		break;
	case OPTION_ZSTD:
		r = archive_write_add_filter_zstd(cpio->archive);
		break;
	case 'j': case 'y':
		r = archive_write_add_filter_bzip2(cpio->archive);
		break;
	case 'z':
		r = archive_write_add_filter_gzip(cpio->archive);
		break;
	case 'Z':
		r = archive_write_add_filter_compress(cpio->archive);
		break;
	default:
		r = archive_write_add_filter_none(cpio->archive);
		break;
	}
	if (r < ARCHIVE_WARN)
		lafe_errc(1, 0, "Requested compression not available");
	switch (cpio->add_filter) {
	case 0:
		r = ARCHIVE_OK;
		break;
	case OPTION_B64ENCODE:
		r = archive_write_add_filter_b64encode(cpio->archive);
		break;
	case OPTION_UUENCODE:
		r = archive_write_add_filter_uuencode(cpio->archive);
		break;
	}
	if (r < ARCHIVE_WARN)
		lafe_errc(1, 0, "Requested filter not available");
	r = archive_write_set_format_by_name(cpio->archive, cpio->format);
	if (r != ARCHIVE_OK)
		lafe_errc(1, 0, "%s", archive_error_string(cpio->archive));
	archive_write_set_bytes_per_block(cpio->archive, cpio->bytes_per_block);
	cpio->linkresolver = archive_entry_linkresolver_new();
	archive_entry_linkresolver_set_strategy(cpio->linkresolver,
	    archive_format(cpio->archive));
	if (cpio->passphrase != NULL)
		r = archive_write_set_passphrase(cpio->archive,
			cpio->passphrase);
	else
		r = archive_write_set_passphrase_callback(cpio->archive, cpio,
			&passphrase_callback);
	if (r != ARCHIVE_OK)
		lafe_errc(1, 0, "%s", archive_error_string(cpio->archive));

	/*
	 * The main loop:  Copy each file into the output archive.
	 */
	r = archive_write_open_filename(cpio->archive, cpio->filename);
	if (r != ARCHIVE_OK)
		lafe_errc(1, 0, "%s", archive_error_string(cpio->archive));
	lr = lafe_line_reader("-", cpio->option_null);
	while ((p = lafe_line_reader_next(lr)) != NULL)
		file_to_archive(cpio, p);
	lafe_line_reader_free(lr);

	/*
	 * The hardlink detection may have queued up a couple of entries
	 * that can now be flushed.
	 */
	entry = NULL;
	archive_entry_linkify(cpio->linkresolver, &entry, &spare);
	while (entry != NULL) {
		entry_to_archive(cpio, entry);
		archive_entry_free(entry);
		entry = NULL;
		archive_entry_linkify(cpio->linkresolver, &entry, &spare);
	}

	r = archive_write_close(cpio->archive);
	if (cpio->dot)
		fprintf(stderr, "\n");
	if (r != ARCHIVE_OK)
		lafe_errc(1, 0, "%s", archive_error_string(cpio->archive));

	if (!cpio->quiet) {
		int64_t blocks =
			(archive_filter_bytes(cpio->archive, 0) + 511)
			/ 512;
		fprintf(stderr, "%lu %s\n", (unsigned long)blocks,
		    blocks == 1 ? "block" : "blocks");
	}
	archive_write_free(cpio->archive);
	archive_entry_linkresolver_free(cpio->linkresolver);
}