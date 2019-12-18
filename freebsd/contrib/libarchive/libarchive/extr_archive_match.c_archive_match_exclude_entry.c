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
struct archive_match {int /*<<< orphan*/  archive; } ;
struct archive_entry {int dummy; } ;
struct archive {int dummy; } ;

/* Variables and functions */
 int ARCHIVE_FAILED ; 
 int /*<<< orphan*/  ARCHIVE_MATCH_MAGIC ; 
 int ARCHIVE_OK ; 
 int /*<<< orphan*/  ARCHIVE_STATE_NEW ; 
 int /*<<< orphan*/  EINVAL ; 
 int add_entry (struct archive_match*,int,struct archive_entry*) ; 
 int /*<<< orphan*/  archive_check_magic (struct archive*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  archive_set_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int validate_time_flag (struct archive*,int,char*) ; 

int
archive_match_exclude_entry(struct archive *_a, int flag,
    struct archive_entry *entry)
{
	struct archive_match *a;
	int r;

	archive_check_magic(_a, ARCHIVE_MATCH_MAGIC,
	    ARCHIVE_STATE_NEW, "archive_match_time_include_entry");
	a = (struct archive_match *)_a;

	if (entry == NULL) {
		archive_set_error(&(a->archive), EINVAL, "entry is NULL");
		return (ARCHIVE_FAILED);
	}
	r = validate_time_flag(_a, flag, "archive_match_exclude_entry");
	if (r != ARCHIVE_OK)
		return (r);
	return (add_entry(a, flag, entry));
}