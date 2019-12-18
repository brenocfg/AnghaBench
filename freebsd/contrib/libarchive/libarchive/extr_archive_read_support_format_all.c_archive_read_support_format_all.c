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
 int /*<<< orphan*/  archive_read_support_format_7zip (struct archive*) ; 
 int /*<<< orphan*/  archive_read_support_format_ar (struct archive*) ; 
 int /*<<< orphan*/  archive_read_support_format_cab (struct archive*) ; 
 int /*<<< orphan*/  archive_read_support_format_cpio (struct archive*) ; 
 int /*<<< orphan*/  archive_read_support_format_empty (struct archive*) ; 
 int /*<<< orphan*/  archive_read_support_format_iso9660 (struct archive*) ; 
 int /*<<< orphan*/  archive_read_support_format_lha (struct archive*) ; 
 int /*<<< orphan*/  archive_read_support_format_mtree (struct archive*) ; 
 int /*<<< orphan*/  archive_read_support_format_rar (struct archive*) ; 
 int /*<<< orphan*/  archive_read_support_format_rar5 (struct archive*) ; 
 int /*<<< orphan*/  archive_read_support_format_tar (struct archive*) ; 
 int /*<<< orphan*/  archive_read_support_format_warc (struct archive*) ; 
 int /*<<< orphan*/  archive_read_support_format_xar (struct archive*) ; 
 int /*<<< orphan*/  archive_read_support_format_zip (struct archive*) ; 

int
archive_read_support_format_all(struct archive *a)
{
	archive_check_magic(a, ARCHIVE_READ_MAGIC,
	    ARCHIVE_STATE_NEW, "archive_read_support_format_all");

	/* TODO: It would be nice to compute the ordering
	 * here automatically so that people who enable just
	 * a few formats can still get the benefits.  That
	 * may just require the format registration to include
	 * a "maximum read-ahead" value (anything that uses seek
	 * would be essentially infinite read-ahead).  The core
	 * bid management can then sort the bidders before calling
	 * them.
	 *
	 * If you implement the above, please return the list below
	 * to alphabetic order.
	 */

	/*
	 * These bidders are all pretty cheap; they just examine a
	 * small initial part of the archive.  If one of these bids
	 * high, we can maybe avoid running any of the more expensive
	 * bidders below.
	 */
	archive_read_support_format_ar(a);
	archive_read_support_format_cpio(a);
	archive_read_support_format_empty(a);
	archive_read_support_format_lha(a);
	archive_read_support_format_mtree(a);
	archive_read_support_format_tar(a);
	archive_read_support_format_xar(a);
	archive_read_support_format_warc(a);

	/*
	 * Install expensive bidders last.  By doing them last, we
	 * increase the chance that a high bid from someone else will
	 * make it unnecessary for these to do anything at all.
	 */
	/* These three have potentially large look-ahead. */
	archive_read_support_format_7zip(a);
	archive_read_support_format_cab(a);
	archive_read_support_format_rar(a);
	archive_read_support_format_rar5(a);
	archive_read_support_format_iso9660(a);
	/* Seek is really bad, since it forces the read-ahead
	 * logic to discard buffered data. */
	archive_read_support_format_zip(a);

	/* Note: We always return ARCHIVE_OK here, even if some of the
	 * above return ARCHIVE_WARN.  The intent here is to enable
	 * "as much as possible."  Clients who need specific
	 * compression should enable those individually so they can
	 * verify the level of support. */
	/* Clear any warning messages set by the above functions. */
	archive_clear_error(a);
	return (ARCHIVE_OK);
}