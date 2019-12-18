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
struct archive {int dummy; } ;

/* Variables and functions */
 int ARCHIVE_OK ; 
 int /*<<< orphan*/  ARCHIVE_READ_MAGIC ; 
 int /*<<< orphan*/  ARCHIVE_STATE_NEW ; 
 int /*<<< orphan*/  archive_check_magic (struct archive*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  archive_clear_error (struct archive*) ; 
 int /*<<< orphan*/  archive_read_support_filter_bzip2 (struct archive*) ; 
 int /*<<< orphan*/  archive_read_support_filter_compress (struct archive*) ; 
 int /*<<< orphan*/  archive_read_support_filter_grzip (struct archive*) ; 
 int /*<<< orphan*/  archive_read_support_filter_gzip (struct archive*) ; 
 int /*<<< orphan*/  archive_read_support_filter_lrzip (struct archive*) ; 
 int /*<<< orphan*/  archive_read_support_filter_lz4 (struct archive*) ; 
 int /*<<< orphan*/  archive_read_support_filter_lzip (struct archive*) ; 
 int /*<<< orphan*/  archive_read_support_filter_lzma (struct archive*) ; 
 int /*<<< orphan*/  archive_read_support_filter_lzop (struct archive*) ; 
 int /*<<< orphan*/  archive_read_support_filter_rpm (struct archive*) ; 
 int /*<<< orphan*/  archive_read_support_filter_uu (struct archive*) ; 
 int /*<<< orphan*/  archive_read_support_filter_xz (struct archive*) ; 
 int /*<<< orphan*/  archive_read_support_filter_zstd (struct archive*) ; 

int
archive_read_support_filter_all(struct archive *a)
{
	archive_check_magic(a, ARCHIVE_READ_MAGIC,
	    ARCHIVE_STATE_NEW, "archive_read_support_filter_all");

	/* Bzip falls back to "bunzip2" command-line */
	archive_read_support_filter_bzip2(a);
	/* The decompress code doesn't use an outside library. */
	archive_read_support_filter_compress(a);
	/* Gzip decompress falls back to "gzip -d" command-line. */
	archive_read_support_filter_gzip(a);
	/* Lzip falls back to "unlzip" command-line program. */
	archive_read_support_filter_lzip(a);
	/* The LZMA file format has a very weak signature, so it
	 * may not be feasible to keep this here, but we'll try.
	 * This will come back out if there are problems. */
	/* Lzma falls back to "unlzma" command-line program. */
	archive_read_support_filter_lzma(a);
	/* Xz falls back to "unxz" command-line program. */
	archive_read_support_filter_xz(a);
	/* The decode code doesn't use an outside library. */
	archive_read_support_filter_uu(a);
	/* The decode code doesn't use an outside library. */
	archive_read_support_filter_rpm(a);
	/* The decode code always uses "lrzip -q -d" command-line. */
	archive_read_support_filter_lrzip(a);
	/* Lzop decompress falls back to "lzop -d" command-line. */
	archive_read_support_filter_lzop(a);
	/* The decode code always uses "grzip -d" command-line. */
	archive_read_support_filter_grzip(a);
	/* Lz4 falls back to "lz4 -d" command-line program. */
	archive_read_support_filter_lz4(a);
	/* Zstd falls back to "zstd -d" command-line program. */
	archive_read_support_filter_zstd(a);

	/* Note: We always return ARCHIVE_OK here, even if some of the
	 * above return ARCHIVE_WARN.  The intent here is to enable
	 * "as much as possible."  Clients who need specific
	 * compression should enable those individually so they can
	 * verify the level of support. */
	/* Clear any warning messages set by the above functions. */
	archive_clear_error(a);
	return (ARCHIVE_OK);
}