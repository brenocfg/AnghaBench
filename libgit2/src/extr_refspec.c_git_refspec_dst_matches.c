#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * dst; } ;
typedef  TYPE_1__ git_refspec ;

/* Variables and functions */
 scalar_t__ wildmatch (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 

int git_refspec_dst_matches(const git_refspec *refspec, const char *refname)
{
	if (refspec == NULL || refspec->dst == NULL)
		return false;

	return (wildmatch(refspec->dst, refname, 0) == 0);
}