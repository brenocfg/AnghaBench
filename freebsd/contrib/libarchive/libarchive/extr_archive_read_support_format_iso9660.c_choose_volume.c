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
struct vd {scalar_t__ location; int /*<<< orphan*/  size; } ;
struct iso9660 {char seenJoliet; int current_position; scalar_t__ seenRockridge; struct vd joliet; struct vd primary; int /*<<< orphan*/  opt_support_joliet; } ;
struct file_info {int dummy; } ;
struct TYPE_2__ {char* archive_format_name; int /*<<< orphan*/  archive_format; } ;
struct archive_read {TYPE_1__ archive; } ;
typedef  int int64_t ;

/* Variables and functions */
 int /*<<< orphan*/  ARCHIVE_ERRNO_MISC ; 
 int ARCHIVE_FATAL ; 
 int /*<<< orphan*/  ARCHIVE_FORMAT_ISO9660_ROCKRIDGE ; 
 scalar_t__ ARCHIVE_OK ; 
 int LOGICAL_BLOCK_SIZE ; 
 void* __archive_read_ahead (struct archive_read*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int __archive_read_consume (struct archive_read*,int) ; 
 scalar_t__ add_entry (struct archive_read*,struct iso9660*,struct file_info*) ; 
 int /*<<< orphan*/  archive_set_error (TYPE_1__*,int /*<<< orphan*/ ,char*) ; 
 struct file_info* parse_file_info (struct archive_read*,int /*<<< orphan*/ *,void const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
choose_volume(struct archive_read *a, struct iso9660 *iso9660)
{
	struct file_info *file;
	int64_t skipsize;
	struct vd *vd;
	const void *block;
	char seenJoliet;

	vd = &(iso9660->primary);
	if (!iso9660->opt_support_joliet)
		iso9660->seenJoliet = 0;
	if (iso9660->seenJoliet &&
		vd->location > iso9660->joliet.location)
		/* This condition is unlikely; by way of caution. */
		vd = &(iso9660->joliet);

	skipsize = LOGICAL_BLOCK_SIZE * (int64_t)vd->location;
	skipsize = __archive_read_consume(a, skipsize);
	if (skipsize < 0)
		return ((int)skipsize);
	iso9660->current_position = skipsize;

	block = __archive_read_ahead(a, vd->size, NULL);
	if (block == NULL) {
		archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
		    "Failed to read full block when scanning "
		    "ISO9660 directory list");
		return (ARCHIVE_FATAL);
	}

	/*
	 * While reading Root Directory, flag seenJoliet must be zero to
	 * avoid converting special name 0x00(Current Directory) and
	 * next byte to UCS2.
	 */
	seenJoliet = iso9660->seenJoliet;/* Save flag. */
	iso9660->seenJoliet = 0;
	file = parse_file_info(a, NULL, block, vd->size);
	if (file == NULL)
		return (ARCHIVE_FATAL);
	iso9660->seenJoliet = seenJoliet;

	/*
	 * If the iso image has both RockRidge and Joliet, we preferentially
	 * use RockRidge Extensions rather than Joliet ones.
	 */
	if (vd == &(iso9660->primary) && iso9660->seenRockridge
	    && iso9660->seenJoliet)
		iso9660->seenJoliet = 0;

	if (vd == &(iso9660->primary) && !iso9660->seenRockridge
	    && iso9660->seenJoliet) {
		/* Switch reading data from primary to joliet. */
		vd = &(iso9660->joliet);
		skipsize = LOGICAL_BLOCK_SIZE * (int64_t)vd->location;
		skipsize -= iso9660->current_position;
		skipsize = __archive_read_consume(a, skipsize);
		if (skipsize < 0)
			return ((int)skipsize);
		iso9660->current_position += skipsize;

		block = __archive_read_ahead(a, vd->size, NULL);
		if (block == NULL) {
			archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
			    "Failed to read full block when scanning "
			    "ISO9660 directory list");
			return (ARCHIVE_FATAL);
		}
		iso9660->seenJoliet = 0;
		file = parse_file_info(a, NULL, block, vd->size);
		if (file == NULL)
			return (ARCHIVE_FATAL);
		iso9660->seenJoliet = seenJoliet;
	}

	/* Store the root directory in the pending list. */
	if (add_entry(a, iso9660, file) != ARCHIVE_OK)
		return (ARCHIVE_FATAL);
	if (iso9660->seenRockridge) {
		a->archive.archive_format = ARCHIVE_FORMAT_ISO9660_ROCKRIDGE;
		a->archive.archive_format_name =
		    "ISO9660 with Rockridge extensions";
	}

	return (ARCHIVE_OK);
}