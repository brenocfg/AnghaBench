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
struct TYPE_3__ {scalar_t__ status; } ;
typedef  TYPE_1__ git_diff_delta ;

/* Variables and functions */
 int /*<<< orphan*/  diff_delta__i2w_path (TYPE_1__ const*) ; 
 int strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int git_diff_delta__i2w_cmp(const void *a, const void *b)
{
	const git_diff_delta *da = a, *db = b;
	int val = strcmp(diff_delta__i2w_path(da), diff_delta__i2w_path(db));
	return val ? val : ((int)da->status - (int)db->status);
}