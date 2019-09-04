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

void test_refs_revparse__disambiguation(void)
{
	/*
	 * $ git show e90810b
	 * tag e90810b
	 * Tagger: Vicent Marti <tanoku@gmail.com>
	 * Date:   Thu Aug 12 03:59:17 2010 +0200
	 *
	 * This is a very simple tag.
	 *
	 * commit e90810b8df3e80c413d903f631643c716887138d
	 * Author: Vicent Marti <tanoku@gmail.com>
	 * Date:   Thu Aug 5 18:42:20 2010 +0200
	 *
	 *     Test commit 2
	 *
	 * diff --git a/readme.txt b/readme.txt
	 * index 6336846..0266163 100644
	 * --- a/readme.txt
	 * +++ b/readme.txt
	 * @@ -1 +1,2 @@
	 *  Testing a readme.txt
	 * +Now we add a single line here
	 *
	 * $ git show-ref e90810b
	 * 7b4384978d2493e851f9cca7858815fac9b10980 refs/tags/e90810b
	 *
	 */
	test_object("e90810b", "7b4384978d2493e851f9cca7858815fac9b10980");

	/*
	 * $ git show e90810
	 * commit e90810b8df3e80c413d903f631643c716887138d
	 * Author: Vicent Marti <tanoku@gmail.com>
	 * Date:   Thu Aug 5 18:42:20 2010 +0200
	 *
	 *     Test commit 2
	 *
	 * diff --git a/readme.txt b/readme.txt
	 * index 6336846..0266163 100644
	 * --- a/readme.txt
	 * +++ b/readme.txt
	 * @@ -1 +1,2 @@
	 *  Testing a readme.txt
	 * +Now we add a single line here
	 */
	test_object("e90810", "e90810b8df3e80c413d903f631643c716887138d");
}