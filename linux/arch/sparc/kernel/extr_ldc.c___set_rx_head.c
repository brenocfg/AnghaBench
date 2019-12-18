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
struct ldc_channel {int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 unsigned long HV_EWOULDBLOCK ; 
 unsigned long sun4v_ldc_rx_set_qhead (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int __set_rx_head(struct ldc_channel *lp, unsigned long head)
{
	int limit = 1000;

	while (limit-- > 0) {
		unsigned long err;

		err = sun4v_ldc_rx_set_qhead(lp->id, head);
		if (!err)
			return 0;

		if (err != HV_EWOULDBLOCK)
			return -EINVAL;

		udelay(1);
	}

	return -EBUSY;
}