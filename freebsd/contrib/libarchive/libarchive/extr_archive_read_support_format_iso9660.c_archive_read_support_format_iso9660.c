#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * first; int /*<<< orphan*/ ** last; } ;
struct TYPE_3__ {int /*<<< orphan*/ * first; int /*<<< orphan*/ ** last; } ;
struct iso9660 {int opt_support_joliet; int opt_support_rockridge; TYPE_2__ re_files; TYPE_1__ cache_files; int /*<<< orphan*/  magic; } ;
struct archive_read {int /*<<< orphan*/  archive; } ;
struct archive {int dummy; } ;

/* Variables and functions */
 int ARCHIVE_FATAL ; 
 int ARCHIVE_OK ; 
 int /*<<< orphan*/  ARCHIVE_READ_MAGIC ; 
 int /*<<< orphan*/  ARCHIVE_STATE_NEW ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  ISO9660_MAGIC ; 
 int __archive_read_register_format (struct archive_read*,struct iso9660*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  archive_check_magic (struct archive*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  archive_read_format_iso9660_bid ; 
 int /*<<< orphan*/  archive_read_format_iso9660_cleanup ; 
 int /*<<< orphan*/  archive_read_format_iso9660_options ; 
 int /*<<< orphan*/  archive_read_format_iso9660_read_data ; 
 int /*<<< orphan*/  archive_read_format_iso9660_read_data_skip ; 
 int /*<<< orphan*/  archive_read_format_iso9660_read_header ; 
 int /*<<< orphan*/  archive_set_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ calloc (int,int) ; 
 int /*<<< orphan*/  free (struct iso9660*) ; 

int
archive_read_support_format_iso9660(struct archive *_a)
{
	struct archive_read *a = (struct archive_read *)_a;
	struct iso9660 *iso9660;
	int r;

	archive_check_magic(_a, ARCHIVE_READ_MAGIC,
	    ARCHIVE_STATE_NEW, "archive_read_support_format_iso9660");

	iso9660 = (struct iso9660 *)calloc(1, sizeof(*iso9660));
	if (iso9660 == NULL) {
		archive_set_error(&a->archive, ENOMEM,
		    "Can't allocate iso9660 data");
		return (ARCHIVE_FATAL);
	}
	iso9660->magic = ISO9660_MAGIC;
	iso9660->cache_files.first = NULL;
	iso9660->cache_files.last = &(iso9660->cache_files.first);
	iso9660->re_files.first = NULL;
	iso9660->re_files.last = &(iso9660->re_files.first);
	/* Enable to support Joliet extensions by default.	*/
	iso9660->opt_support_joliet = 1;
	/* Enable to support Rock Ridge extensions by default.	*/
	iso9660->opt_support_rockridge = 1;

	r = __archive_read_register_format(a,
	    iso9660,
	    "iso9660",
	    archive_read_format_iso9660_bid,
	    archive_read_format_iso9660_options,
	    archive_read_format_iso9660_read_header,
	    archive_read_format_iso9660_read_data,
	    archive_read_format_iso9660_read_data_skip,
	    NULL,
	    archive_read_format_iso9660_cleanup,
	    NULL,
	    NULL);

	if (r != ARCHIVE_OK) {
		free(iso9660);
		return (r);
	}
	return (ARCHIVE_OK);
}