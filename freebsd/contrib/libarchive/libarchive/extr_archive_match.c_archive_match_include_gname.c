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
struct archive_match {int /*<<< orphan*/  inclusion_gnames; } ;
struct archive {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARCHIVE_MATCH_MAGIC ; 
 int /*<<< orphan*/  ARCHIVE_STATE_NEW ; 
 int add_owner_name (struct archive_match*,int /*<<< orphan*/ *,int,char const*) ; 
 int /*<<< orphan*/  archive_check_magic (struct archive*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

int
archive_match_include_gname(struct archive *_a, const char *gname)
{
	struct archive_match *a;

	archive_check_magic(_a, ARCHIVE_MATCH_MAGIC,
	    ARCHIVE_STATE_NEW, "archive_match_include_gname");
	a = (struct archive_match *)_a;
	return (add_owner_name(a, &(a->inclusion_gnames), 1, gname));
}