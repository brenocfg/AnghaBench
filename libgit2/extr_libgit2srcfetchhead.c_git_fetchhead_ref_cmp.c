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
struct TYPE_2__ {scalar_t__ ref_name; scalar_t__ is_merge; } ;
typedef  TYPE_1__ git_fetchhead_ref ;

/* Variables and functions */
 int strcmp (scalar_t__,scalar_t__) ; 

int git_fetchhead_ref_cmp(const void *a, const void *b)
{
	const git_fetchhead_ref *one = (const git_fetchhead_ref *)a;
	const git_fetchhead_ref *two = (const git_fetchhead_ref *)b;

	if (one->is_merge && !two->is_merge)
		return -1;
	if (two->is_merge && !one->is_merge)
		return 1;

	if (one->ref_name && two->ref_name)
		return strcmp(one->ref_name, two->ref_name);
	else if (one->ref_name)
		return -1;
	else if (two->ref_name)
		return 1;

	return 0;
}