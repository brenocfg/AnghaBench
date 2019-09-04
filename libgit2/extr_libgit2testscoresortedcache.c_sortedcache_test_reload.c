#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int value; char smaller_value; } ;
typedef  TYPE_1__ sortedcache_test_struct ;
typedef  int /*<<< orphan*/  git_sortedcache ;
struct TYPE_7__ {char* ptr; } ;
typedef  TYPE_2__ git_buf ;

/* Variables and functions */
 TYPE_2__ GIT_BUF_INIT ; 
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 scalar_t__ git__isspace (char) ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_2__*) ; 
 int /*<<< orphan*/  git_sortedcache_clear (int /*<<< orphan*/ *,int) ; 
 scalar_t__ git_sortedcache_lockandload (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  git_sortedcache_upsert (void**,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  git_sortedcache_wunlock (int /*<<< orphan*/ *) ; 
 int strtol (char*,char**,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sortedcache_test_reload(git_sortedcache *sc)
{
	int count = 0;
	git_buf buf = GIT_BUF_INIT;
	char *scan, *after;
	sortedcache_test_struct *item;

	cl_assert(git_sortedcache_lockandload(sc, &buf) > 0);

	git_sortedcache_clear(sc, false); /* clear once we already have lock */

	for (scan = buf.ptr; *scan; scan = after + 1) {
		int val = strtol(scan, &after, 0);
		cl_assert(after > scan);
		scan = after;

		for (scan = after; git__isspace(*scan); ++scan) /* find start */;
		for (after = scan; *after && *after != '\n'; ++after) /* find eol */;
		*after = '\0';

		cl_git_pass(git_sortedcache_upsert((void **)&item, sc, scan));

		item->value = val;
		item->smaller_value = (char)(count++);
	}

	git_sortedcache_wunlock(sc);

	git_buf_dispose(&buf);
}