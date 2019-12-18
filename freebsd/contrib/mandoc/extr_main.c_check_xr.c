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
struct mansearch {int firstmatch; int /*<<< orphan*/  argmode; int /*<<< orphan*/ * outkey; int /*<<< orphan*/  sec; int /*<<< orphan*/ * arch; } ;
struct manpaths {scalar_t__ sz; } ;
struct mandoc_xr {int line; int count; int /*<<< orphan*/  sec; int /*<<< orphan*/  name; scalar_t__ pos; struct mandoc_xr* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARG_NAME ; 
 int /*<<< orphan*/  MANDOCERR_XR_BAD ; 
 int fs_search (struct mansearch*,struct manpaths*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t*) ; 
 int /*<<< orphan*/  mandoc_msg (int /*<<< orphan*/ ,int,scalar_t__,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 struct mandoc_xr* mandoc_xr_get () ; 
 int /*<<< orphan*/  manpath_base (struct manpaths*) ; 
 scalar_t__ mansearch (struct mansearch*,struct manpaths*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t*) ; 

__attribute__((used)) static void
check_xr(void)
{
	static struct manpaths	 paths;
	struct mansearch	 search;
	struct mandoc_xr	*xr;
	size_t			 sz;

	if (paths.sz == 0)
		manpath_base(&paths);

	for (xr = mandoc_xr_get(); xr != NULL; xr = xr->next) {
		if (xr->line == -1)
			continue;
		search.arch = NULL;
		search.sec = xr->sec;
		search.outkey = NULL;
		search.argmode = ARG_NAME;
		search.firstmatch = 1;
		if (mansearch(&search, &paths, 1, &xr->name, NULL, &sz))
			continue;
		if (fs_search(&search, &paths, 1, &xr->name, NULL, &sz) != -1)
			continue;
		if (xr->count == 1)
			mandoc_msg(MANDOCERR_XR_BAD, xr->line,
			    xr->pos + 1, "Xr %s %s", xr->name, xr->sec);
		else
			mandoc_msg(MANDOCERR_XR_BAD, xr->line,
			    xr->pos + 1, "Xr %s %s (%d times)",
			    xr->name, xr->sec, xr->count);
	}
}