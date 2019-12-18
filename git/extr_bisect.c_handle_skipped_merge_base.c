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
struct object_id {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  _ (char*) ; 
 struct object_id const* current_bad_oid ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  good_revs ; 
 char* join_sha1_array_hex (int /*<<< orphan*/ *,char) ; 
 char* oid_to_hex (struct object_id const*) ; 
 int /*<<< orphan*/  term_bad ; 
 int /*<<< orphan*/  warning (int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ,char*,char*) ; 

__attribute__((used)) static void handle_skipped_merge_base(const struct object_id *mb)
{
	char *mb_hex = oid_to_hex(mb);
	char *bad_hex = oid_to_hex(current_bad_oid);
	char *good_hex = join_sha1_array_hex(&good_revs, ' ');

	warning(_("the merge base between %s and [%s] "
		"must be skipped.\n"
		"So we cannot be sure the first %s commit is "
		"between %s and %s.\n"
		"We continue anyway."),
		bad_hex, good_hex, term_bad, mb_hex, bad_hex);
	free(good_hex);
}