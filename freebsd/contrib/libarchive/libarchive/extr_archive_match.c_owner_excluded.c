#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ count; } ;
struct TYPE_5__ {scalar_t__ count; } ;
struct archive_match {TYPE_1__ inclusion_gnames; TYPE_1__ inclusion_unames; TYPE_3__ inclusion_gids; TYPE_3__ inclusion_uids; } ;
struct archive_entry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  archive_entry_gid (struct archive_entry*) ; 
 int /*<<< orphan*/  archive_entry_gname (struct archive_entry*) ; 
 int /*<<< orphan*/  archive_entry_gname_w (struct archive_entry*) ; 
 int /*<<< orphan*/  archive_entry_uid (struct archive_entry*) ; 
 int /*<<< orphan*/  archive_entry_uname (struct archive_entry*) ; 
 int /*<<< orphan*/  archive_entry_uname_w (struct archive_entry*) ; 
 int /*<<< orphan*/  match_owner_id (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int match_owner_name_mbs (struct archive_match*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int match_owner_name_wcs (struct archive_match*,TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
owner_excluded(struct archive_match *a, struct archive_entry *entry)
{
	int r;

	if (a->inclusion_uids.count) {
		if (!match_owner_id(&(a->inclusion_uids),
		    archive_entry_uid(entry)))
			return (1);
	}

	if (a->inclusion_gids.count) {
		if (!match_owner_id(&(a->inclusion_gids),
		    archive_entry_gid(entry)))
			return (1);
	}

	if (a->inclusion_unames.count) {
#if defined(_WIN32) && !defined(__CYGWIN__)
		r = match_owner_name_wcs(a, &(a->inclusion_unames),
			archive_entry_uname_w(entry));
#else
		r = match_owner_name_mbs(a, &(a->inclusion_unames),
			archive_entry_uname(entry));
#endif
		if (!r)
			return (1);
		else if (r < 0)
			return (r);
	}

	if (a->inclusion_gnames.count) {
#if defined(_WIN32) && !defined(__CYGWIN__)
		r = match_owner_name_wcs(a, &(a->inclusion_gnames),
			archive_entry_gname_w(entry));
#else
		r = match_owner_name_mbs(a, &(a->inclusion_gnames),
			archive_entry_gname(entry));
#endif
		if (!r)
			return (1);
		else if (r < 0)
			return (r);
	}
	return (0);
}