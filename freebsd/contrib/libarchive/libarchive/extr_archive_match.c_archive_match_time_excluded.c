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
struct archive_match {int setflag; int /*<<< orphan*/  archive; } ;
struct archive_entry {int dummy; } ;
struct archive {int dummy; } ;

/* Variables and functions */
 int ARCHIVE_FAILED ; 
 int /*<<< orphan*/  ARCHIVE_MATCH_MAGIC ; 
 int /*<<< orphan*/  ARCHIVE_STATE_NEW ; 
 int /*<<< orphan*/  EINVAL ; 
 int TIME_IS_SET ; 
 int /*<<< orphan*/  archive_check_magic (struct archive*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  archive_set_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int time_excluded (struct archive_match*,struct archive_entry*) ; 

int
archive_match_time_excluded(struct archive *_a,
    struct archive_entry *entry)
{
	struct archive_match *a;

	archive_check_magic(_a, ARCHIVE_MATCH_MAGIC,
	    ARCHIVE_STATE_NEW, "archive_match_time_excluded_ae");

	a = (struct archive_match *)_a;
	if (entry == NULL) {
		archive_set_error(&(a->archive), EINVAL, "entry is NULL");
		return (ARCHIVE_FAILED);
	}

	/* If we don't have inclusion time set at all, the entry is always
	 * not excluded. */
	if ((a->setflag & TIME_IS_SET) == 0)
		return (0);
	return (time_excluded(a, entry));
}