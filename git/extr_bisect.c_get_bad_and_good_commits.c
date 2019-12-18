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
struct repository {int dummy; } ;
struct commit {int dummy; } ;
struct TYPE_2__ {int nr; scalar_t__ oid; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOC_ARRAY (struct commit**,int) ; 
 scalar_t__ current_bad_oid ; 
 struct commit* get_commit_reference (struct repository*,scalar_t__) ; 
 TYPE_1__ good_revs ; 

__attribute__((used)) static struct commit **get_bad_and_good_commits(struct repository *r,
						int *rev_nr)
{
	struct commit **rev;
	int i, n = 0;

	ALLOC_ARRAY(rev, 1 + good_revs.nr);
	rev[n++] = get_commit_reference(r, current_bad_oid);
	for (i = 0; i < good_revs.nr; i++)
		rev[n++] = get_commit_reference(r, good_revs.oid + i);
	*rev_nr = n;

	return rev;
}