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
struct diff_options {int dummy; } ;
struct diff_filepair {TYPE_1__* two; TYPE_1__* one; } ;
struct TYPE_2__ {int /*<<< orphan*/  mode; } ;

/* Variables and functions */
 scalar_t__ DIFF_FILE_VALID (TYPE_1__*) ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 scalar_t__ diff_unmodified_pair (struct diff_filepair*) ; 
 int /*<<< orphan*/  run_diff (struct diff_filepair*,struct diff_options*) ; 

__attribute__((used)) static void diff_flush_patch(struct diff_filepair *p, struct diff_options *o)
{
	if (diff_unmodified_pair(p))
		return;

	if ((DIFF_FILE_VALID(p->one) && S_ISDIR(p->one->mode)) ||
	    (DIFF_FILE_VALID(p->two) && S_ISDIR(p->two->mode)))
		return; /* no tree diffs in patch format */

	run_diff(p, o);
}