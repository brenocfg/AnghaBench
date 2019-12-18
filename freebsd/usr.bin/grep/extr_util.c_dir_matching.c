#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ mode; int /*<<< orphan*/  pat; } ;

/* Variables and functions */
 scalar_t__ EXCL_PAT ; 
 scalar_t__ dinclude ; 
 TYPE_1__* dpattern ; 
 unsigned int dpatterns ; 
 scalar_t__ fnmatch (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool
dir_matching(const char *dname)
{
	bool ret;

	ret = dinclude ? false : true;

	for (unsigned int i = 0; i < dpatterns; ++i) {
		if (dname != NULL && fnmatch(dpattern[i].pat, dname, 0) == 0)
			/*
			 * The last pattern matched wins exclusion/inclusion
			 * rights, so we can't reasonably bail out early here.
			 */
			ret = (dpattern[i].mode != EXCL_PAT);
	}
	return (ret);
}