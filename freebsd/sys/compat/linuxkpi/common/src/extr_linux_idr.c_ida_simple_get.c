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
struct ida {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int EAGAIN ; 
 int ENOMEM ; 
 int ENOSPC ; 
 int /*<<< orphan*/  MPASS (int) ; 
 scalar_t__ __predict_false (int) ; 
 int ida_get_new_above (struct ida*,unsigned int,int*) ; 
 int /*<<< orphan*/  ida_pre_get (struct ida*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ida_remove (struct ida*,int) ; 

int
ida_simple_get(struct ida *ida, unsigned int start, unsigned int end,
    gfp_t flags)
{
	int ret, id;
	unsigned int max;

	MPASS((int)start >= 0);
	MPASS((int)end >= 0);

	if (end == 0)
		max = 0x80000000;
	else {
		MPASS(end > start);
		max = end - 1;
	}
again:
	if (!ida_pre_get(ida, flags))
		return (-ENOMEM);

	if ((ret = ida_get_new_above(ida, start, &id)) == 0) {
		if (id > max) {
			ida_remove(ida, id);
			ret = -ENOSPC;
		} else {
			ret = id;
		}
	}
	if (__predict_false(ret == -EAGAIN))
		goto again;

	return (ret);
}