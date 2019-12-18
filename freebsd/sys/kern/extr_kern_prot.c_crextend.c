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
struct ucred {int cr_agroups; scalar_t__ cr_groups; scalar_t__ cr_smallgroups; } ;
typedef  int /*<<< orphan*/  gid_t ;

/* Variables and functions */
 int MINALLOCSIZE ; 
 int /*<<< orphan*/  M_CRED ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  free (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ malloc (int,int /*<<< orphan*/ ,int) ; 
 int roundup2 (int,int) ; 

void
crextend(struct ucred *cr, int n)
{
	int cnt;

	/* Truncate? */
	if (n <= cr->cr_agroups)
		return;

	/*
	 * We extend by 2 each time since we're using a power of two
	 * allocator until we need enough groups to fill a page.
	 * Once we're allocating multiple pages, only allocate as many
	 * as we actually need.  The case of processes needing a
	 * non-power of two number of pages seems more likely than
	 * a real world process that adds thousands of groups one at a
	 * time.
	 */
	if ( n < PAGE_SIZE / sizeof(gid_t) ) {
		if (cr->cr_agroups == 0)
			cnt = MINALLOCSIZE / sizeof(gid_t);
		else
			cnt = cr->cr_agroups * 2;

		while (cnt < n)
			cnt *= 2;
	} else
		cnt = roundup2(n, PAGE_SIZE / sizeof(gid_t));

	/* Free the old array. */
	if (cr->cr_groups != cr->cr_smallgroups)
		free(cr->cr_groups, M_CRED);

	cr->cr_groups = malloc(cnt * sizeof(gid_t), M_CRED, M_WAITOK | M_ZERO);
	cr->cr_agroups = cnt;
}