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

/* Variables and functions */
 int /*<<< orphan*/  test_object (char*,char*) ; 

void test_refs_revparse__date(void)
{
	/*
	 * $ git reflog HEAD --date=iso
	 * a65fedf HEAD@{2012-04-30 08:23:41 -0900}: checkout: moving from br2 to master
	 * a4a7dce HEAD@{2012-04-30 08:23:37 -0900}: commit: checking in
	 * c47800c HEAD@{2012-04-30 08:23:28 -0900}: checkout: moving from master to br2
	 * a65fedf HEAD@{2012-04-30 08:23:23 -0900}: commit:
	 * be3563a HEAD@{2012-04-30 10:22:43 -0700}: clone: from /Users/ben/src/libgit2/tes
	 *
	 * $ git reflog HEAD --date=raw
	 * a65fedf HEAD@{1335806621 -0900}: checkout: moving from br2 to master
	 * a4a7dce HEAD@{1335806617 -0900}: commit: checking in
	 * c47800c HEAD@{1335806608 -0900}: checkout: moving from master to br2
	 * a65fedf HEAD@{1335806603 -0900}: commit:
	 * be3563a HEAD@{1335806563 -0700}: clone: from /Users/ben/src/libgit2/tests/resour
	 */
	test_object("HEAD@{10 years ago}", NULL);

	test_object("HEAD@{1 second}", "a65fedf39aefe402d3bb6e24df4d4f5fe4547750");
	test_object("HEAD@{1 second ago}", "a65fedf39aefe402d3bb6e24df4d4f5fe4547750");
	test_object("HEAD@{2 days ago}", "a65fedf39aefe402d3bb6e24df4d4f5fe4547750");

	/*
	 * $ git reflog master --date=iso
	 * a65fedf master@{2012-04-30 09:23:23 -0800}: commit: checking in
	 * be3563a master@{2012-04-30 09:22:43 -0800}: clone: from /Users/ben/src...
	 *
	 * $ git reflog master --date=raw
	 * a65fedf master@{1335806603 -0800}: commit: checking in
	 * be3563a master@{1335806563 -0800}: clone: from /Users/ben/src/libgit2/tests/reso
	 */


	/*
	 * $ git reflog -1 "master@{2012-04-30 17:22:42 +0000}"
	 * warning: Log for 'master' only goes back to Mon, 30 Apr 2012 09:22:43 -0800.
	 */
	test_object("master@{2012-04-30 17:22:42 +0000}", NULL);
	test_object("master@{2012-04-30 09:22:42 -0800}", NULL);

	/*
	 * $ git reflog -1 "master@{2012-04-30 17:22:43 +0000}"
	 * be3563a master@{Mon Apr 30 09:22:43 2012 -0800}: clone: from /Users/ben/src/libg
	 */
	test_object("master@{2012-04-30 17:22:43 +0000}", "be3563ae3f795b2b4353bcce3a527ad0a4f7f644");
	test_object("master@{2012-04-30 09:22:43 -0800}", "be3563ae3f795b2b4353bcce3a527ad0a4f7f644");

	/*
	 * $ git reflog -1 "master@{2012-4-30 09:23:27 -0800}"
	 * a65fedf master@{Mon Apr 30 09:23:23 2012 -0800}: commit: checking in
	 */
	test_object("master@{2012-4-30 09:23:27 -0800}", "a65fedf39aefe402d3bb6e24df4d4f5fe4547750");

	/*
	 * $ git reflog -1 master@{2012-05-03}
	 * a65fedf master@{Mon Apr 30 09:23:23 2012 -0800}: commit: checking in
	 */
	test_object("master@{2012-05-03}", "a65fedf39aefe402d3bb6e24df4d4f5fe4547750");

	/*
	 * $ git reflog -1 "master@{1335806603}"
	 * a65fedf
	 *
	 * $ git reflog -1 "master@{1335806602}"
	 * be3563a
	 */
	test_object("master@{1335806603}", "a65fedf39aefe402d3bb6e24df4d4f5fe4547750");
	test_object("master@{1335806602}", "be3563ae3f795b2b4353bcce3a527ad0a4f7f644");
}