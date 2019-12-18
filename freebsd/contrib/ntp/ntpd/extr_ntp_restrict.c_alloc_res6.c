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
typedef  int /*<<< orphan*/  restrict_u ;

/* Variables and functions */
 size_t INC_RESLIST6 ; 
 int /*<<< orphan*/  INSIST (int) ; 
 int /*<<< orphan*/  LINK_SLIST (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UNLINK_HEAD_SLIST (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t V6_SIZEOF_RESTRICT_U ; 
 int /*<<< orphan*/ * eallocarray (size_t const,size_t const) ; 
 int /*<<< orphan*/  link ; 
 int /*<<< orphan*/  resfree6 ; 

__attribute__((used)) static restrict_u *
alloc_res6(void)
{
	const size_t	cb = V6_SIZEOF_RESTRICT_U;
	const size_t	count = INC_RESLIST6;
	restrict_u *	rl;
	restrict_u *	res;
	size_t		i;

	UNLINK_HEAD_SLIST(res, resfree6, link);
	if (res != NULL)
		return res;

	rl = eallocarray(count, cb);
	/* link all but the first onto free list */
	res = (void *)((char *)rl + (count - 1) * cb);
	for (i = count - 1; i > 0; i--) {
		LINK_SLIST(resfree6, res, link);
		res = (void *)((char *)res - cb);
	}
	INSIST(rl == res);
	/* allocate the first */
	return res;
}