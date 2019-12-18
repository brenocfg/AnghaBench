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
struct ldc_channel {int /*<<< orphan*/  rx_tail; } ;

/* Variables and functions */
 int __set_rx_head (struct ldc_channel*,int /*<<< orphan*/ ) ; 

int ldc_rx_reset(struct ldc_channel *lp)
{
	return __set_rx_head(lp, lp->rx_tail);
}