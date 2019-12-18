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
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  uid_t ;
typedef  int /*<<< orphan*/  time_t ;
struct archive_entry {int dummy; } ;
struct ar {int entry_padding; int entry_bytes_remaining; scalar_t__ entry_offset; } ;
typedef  int /*<<< orphan*/  mode_t ;
typedef  int /*<<< orphan*/  gid_t ;

/* Variables and functions */
 int /*<<< orphan*/  AE_IFREG ; 
 int ARCHIVE_OK ; 
 int AR_date_offset ; 
 int /*<<< orphan*/  AR_date_size ; 
 int AR_gid_offset ; 
 int /*<<< orphan*/  AR_gid_size ; 
 int AR_mode_offset ; 
 int /*<<< orphan*/  AR_mode_size ; 
 int AR_size_offset ; 
 int /*<<< orphan*/  AR_size_size ; 
 int AR_uid_offset ; 
 int /*<<< orphan*/  AR_uid_size ; 
 int ar_atol10 (char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ ar_atol8 (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  archive_entry_set_filetype (struct archive_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  archive_entry_set_gid (struct archive_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  archive_entry_set_mode (struct archive_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  archive_entry_set_mtime (struct archive_entry*,int /*<<< orphan*/ ,long) ; 
 int /*<<< orphan*/  archive_entry_set_size (struct archive_entry*,int) ; 
 int /*<<< orphan*/  archive_entry_set_uid (struct archive_entry*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ar_parse_common_header(struct ar *ar, struct archive_entry *entry,
    const char *h)
{
	uint64_t n;

	/* Copy remaining header */
	archive_entry_set_filetype(entry, AE_IFREG);
	archive_entry_set_mtime(entry,
	    (time_t)ar_atol10(h + AR_date_offset, AR_date_size), 0L);
	archive_entry_set_uid(entry,
	    (uid_t)ar_atol10(h + AR_uid_offset, AR_uid_size));
	archive_entry_set_gid(entry,
	    (gid_t)ar_atol10(h + AR_gid_offset, AR_gid_size));
	archive_entry_set_mode(entry,
	    (mode_t)ar_atol8(h + AR_mode_offset, AR_mode_size));
	n = ar_atol10(h + AR_size_offset, AR_size_size);

	ar->entry_offset = 0;
	ar->entry_padding = n % 2;
	archive_entry_set_size(entry, n);
	ar->entry_bytes_remaining = n;
	return (ARCHIVE_OK);
}