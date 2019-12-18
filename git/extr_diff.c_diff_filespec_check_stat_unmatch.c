#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct repository {int dummy; } ;
struct diff_filepair {int done_skip_stat_unmatch; int skip_stat_unmatch_result; TYPE_1__* two; TYPE_1__* one; } ;
struct TYPE_5__ {scalar_t__ mode; scalar_t__ size; scalar_t__ oid_valid; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_SIZE_ONLY ; 
 int /*<<< orphan*/  DIFF_FILE_VALID (TYPE_1__*) ; 
 int /*<<< orphan*/  diff_filespec_is_identical (struct repository*,TYPE_1__*,TYPE_1__*) ; 
 scalar_t__ diff_populate_filespec (struct repository*,TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int diff_filespec_check_stat_unmatch(struct repository *r,
					    struct diff_filepair *p)
{
	if (p->done_skip_stat_unmatch)
		return p->skip_stat_unmatch_result;

	p->done_skip_stat_unmatch = 1;
	p->skip_stat_unmatch_result = 0;
	/*
	 * 1. Entries that come from stat info dirtiness
	 *    always have both sides (iow, not create/delete),
	 *    one side of the object name is unknown, with
	 *    the same mode and size.  Keep the ones that
	 *    do not match these criteria.  They have real
	 *    differences.
	 *
	 * 2. At this point, the file is known to be modified,
	 *    with the same mode and size, and the object
	 *    name of one side is unknown.  Need to inspect
	 *    the identical contents.
	 */
	if (!DIFF_FILE_VALID(p->one) || /* (1) */
	    !DIFF_FILE_VALID(p->two) ||
	    (p->one->oid_valid && p->two->oid_valid) ||
	    (p->one->mode != p->two->mode) ||
	    diff_populate_filespec(r, p->one, CHECK_SIZE_ONLY) ||
	    diff_populate_filespec(r, p->two, CHECK_SIZE_ONLY) ||
	    (p->one->size != p->two->size) ||
	    !diff_filespec_is_identical(r, p->one, p->two)) /* (2) */
		p->skip_stat_unmatch_result = 1;
	return p->skip_stat_unmatch_result;
}