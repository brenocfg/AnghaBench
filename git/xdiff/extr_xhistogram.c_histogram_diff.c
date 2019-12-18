#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xpparam_t ;
struct TYPE_8__ {int* rchg; } ;
struct TYPE_7__ {int* rchg; } ;
struct TYPE_9__ {TYPE_2__ xdf2; TYPE_1__ xdf1; } ;
typedef  TYPE_3__ xdfenv_t ;
struct region {int begin1; int begin2; int end1; int end2; } ;
typedef  int /*<<< orphan*/  lcs ;

/* Variables and functions */
 scalar_t__ LINE_END (int) ; 
 scalar_t__ MAX_PTR ; 
 int fall_back_to_classic_diff (int /*<<< orphan*/  const*,TYPE_3__*,int,int,int,int) ; 
 int find_lcs (int /*<<< orphan*/  const*,TYPE_3__*,struct region*,int,int,int,int) ; 
 int /*<<< orphan*/  memset (struct region*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int histogram_diff(xpparam_t const *xpp, xdfenv_t *env,
	int line1, int count1, int line2, int count2)
{
	struct region lcs;
	int lcs_found;
	int result;
redo:
	result = -1;

	if (count1 <= 0 && count2 <= 0)
		return 0;

	if (LINE_END(1) >= MAX_PTR)
		return -1;

	if (!count1) {
		while(count2--)
			env->xdf2.rchg[line2++ - 1] = 1;
		return 0;
	} else if (!count2) {
		while(count1--)
			env->xdf1.rchg[line1++ - 1] = 1;
		return 0;
	}

	memset(&lcs, 0, sizeof(lcs));
	lcs_found = find_lcs(xpp, env, &lcs, line1, count1, line2, count2);
	if (lcs_found < 0)
		goto out;
	else if (lcs_found)
		result = fall_back_to_classic_diff(xpp, env, line1, count1, line2, count2);
	else {
		if (lcs.begin1 == 0 && lcs.begin2 == 0) {
			while (count1--)
				env->xdf1.rchg[line1++ - 1] = 1;
			while (count2--)
				env->xdf2.rchg[line2++ - 1] = 1;
			result = 0;
		} else {
			result = histogram_diff(xpp, env,
						line1, lcs.begin1 - line1,
						line2, lcs.begin2 - line2);
			if (result)
				goto out;
			/*
			 * result = histogram_diff(xpp, env,
			 *            lcs.end1 + 1, LINE_END(1) - lcs.end1,
			 *            lcs.end2 + 1, LINE_END(2) - lcs.end2);
			 * but let's optimize tail recursion ourself:
			*/
			count1 = LINE_END(1) - lcs.end1;
			line1 = lcs.end1 + 1;
			count2 = LINE_END(2) - lcs.end2;
			line2 = lcs.end2 + 1;
			goto redo;
		}
	}
out:
	return result;
}