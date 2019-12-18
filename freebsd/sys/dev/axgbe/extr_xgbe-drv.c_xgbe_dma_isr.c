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
struct xgbe_channel {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  xgbe_one_poll (struct xgbe_channel*,int) ; 

__attribute__((used)) static void xgbe_dma_isr(void *data)
{
	struct xgbe_channel *channel = data;

	xgbe_one_poll(channel, 16);
}