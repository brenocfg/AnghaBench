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
typedef  enum md_types { ____Placeholder_md_types } md_types ;

/* Variables and functions */
#define  MD_MALLOC 130 
#define  MD_SWAP 129 
#define  MD_VNODE 128 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  errx (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mdname ; 
 int /*<<< orphan*/  path_mdconfig ; 
 int run (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,char const*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  run_exitnumber (int) ; 
 int /*<<< orphan*/  run_exitstr (int) ; 
 int /*<<< orphan*/  unit ; 

__attribute__((used)) static void
do_mdconfig_attach(const char *args, const enum md_types mdtype)
{
	int rv;
	const char *ta;		/* Type arg. */

	switch (mdtype) {
	case MD_SWAP:
		ta = "-t swap";
		break;
	case MD_VNODE:
		ta = "-t vnode";
		break;
	case MD_MALLOC:
		ta = "-t malloc";
		break;
	default:
		abort();
	}
	rv = run(NULL, "%s -a %s%s -u %s%d", path_mdconfig, ta, args,
	    mdname, unit);
	if (rv)
		errx(1, "mdconfig (attach) exited %s %d", run_exitstr(rv),
		    run_exitnumber(rv));
}