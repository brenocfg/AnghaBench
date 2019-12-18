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
typedef  union ctl_io {int dummy; } ctl_io ;
typedef  int /*<<< orphan*/  uint64_t ;
struct ctl_scsiio {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  len; int /*<<< orphan*/  lba; } ;
struct ctl_error_desc {int error_pattern; TYPE_1__ lba_range; } ;
struct ctl_cmd_entry {int pattern; } ;
typedef  int ctl_lun_error_pattern ;
typedef  scalar_t__ ctl_action ;

/* Variables and functions */
 scalar_t__ CTL_ACTION_PASS ; 
 int CTL_LUN_PAT_ANY ; 
 int CTL_LUN_PAT_CMD ; 
 int CTL_LUN_PAT_MASK ; 
 int CTL_LUN_PAT_NONE ; 
 int CTL_LUN_PAT_RANGE ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ ctl_extent_check_lba (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ctl_cmd_entry* ctl_get_cmd_entry (struct ctl_scsiio*,int /*<<< orphan*/ *) ; 
 int ctl_get_lba_len (union ctl_io*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static ctl_lun_error_pattern
ctl_cmd_pattern_match(struct ctl_scsiio *ctsio, struct ctl_error_desc *desc)
{
	const struct ctl_cmd_entry *entry;
	ctl_lun_error_pattern filtered_pattern, pattern;

	pattern = desc->error_pattern;

	/*
	 * XXX KDM we need more data passed into this function to match a
	 * custom pattern, and we actually need to implement custom pattern
	 * matching.
	 */
	if (pattern & CTL_LUN_PAT_CMD)
		return (CTL_LUN_PAT_CMD);

	if ((pattern & CTL_LUN_PAT_MASK) == CTL_LUN_PAT_ANY)
		return (CTL_LUN_PAT_ANY);

	entry = ctl_get_cmd_entry(ctsio, NULL);

	filtered_pattern = entry->pattern & pattern;

	/*
	 * If the user requested specific flags in the pattern (e.g.
	 * CTL_LUN_PAT_RANGE), make sure the command supports all of those
	 * flags.
	 *
	 * If the user did not specify any flags, it doesn't matter whether
	 * or not the command supports the flags.
	 */
	if ((filtered_pattern & ~CTL_LUN_PAT_MASK) !=
	     (pattern & ~CTL_LUN_PAT_MASK))
		return (CTL_LUN_PAT_NONE);

	/*
	 * If the user asked for a range check, see if the requested LBA
	 * range overlaps with this command's LBA range.
	 */
	if (filtered_pattern & CTL_LUN_PAT_RANGE) {
		uint64_t lba1;
		uint64_t len1;
		ctl_action action;
		int retval;

		retval = ctl_get_lba_len((union ctl_io *)ctsio, &lba1, &len1);
		if (retval != 0)
			return (CTL_LUN_PAT_NONE);

		action = ctl_extent_check_lba(lba1, len1, desc->lba_range.lba,
					      desc->lba_range.len, FALSE);
		/*
		 * A "pass" means that the LBA ranges don't overlap, so
		 * this doesn't match the user's range criteria.
		 */
		if (action == CTL_ACTION_PASS)
			return (CTL_LUN_PAT_NONE);
	}

	return (filtered_pattern);
}