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
struct TYPE_4__ {struct archive_match* ids; } ;
struct TYPE_3__ {struct archive_match* ids; } ;
struct archive_match {int /*<<< orphan*/  inclusion_gnames; int /*<<< orphan*/  inclusion_unames; TYPE_2__ inclusion_gids; TYPE_1__ inclusion_uids; int /*<<< orphan*/  exclusion_entry_list; int /*<<< orphan*/  exclusions; int /*<<< orphan*/  inclusions; } ;
struct archive {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARCHIVE_MATCH_MAGIC ; 
 int ARCHIVE_OK ; 
 int ARCHIVE_STATE_ANY ; 
 int ARCHIVE_STATE_FATAL ; 
 int /*<<< orphan*/  archive_check_magic (struct archive*,int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  entry_list_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (struct archive_match*) ; 
 int /*<<< orphan*/  match_list_free (int /*<<< orphan*/ *) ; 

int
archive_match_free(struct archive *_a)
{
	struct archive_match *a;

	if (_a == NULL)
		return (ARCHIVE_OK);
	archive_check_magic(_a, ARCHIVE_MATCH_MAGIC,
	    ARCHIVE_STATE_ANY | ARCHIVE_STATE_FATAL, "archive_match_free");
	a = (struct archive_match *)_a;
	match_list_free(&(a->inclusions));
	match_list_free(&(a->exclusions));
	entry_list_free(&(a->exclusion_entry_list));
	free(a->inclusion_uids.ids);
	free(a->inclusion_gids.ids);
	match_list_free(&(a->inclusion_unames));
	match_list_free(&(a->inclusion_gnames));
	free(a);
	return (ARCHIVE_OK);
}