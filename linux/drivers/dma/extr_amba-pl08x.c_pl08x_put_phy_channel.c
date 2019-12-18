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
struct pl08x_phy_chan {int /*<<< orphan*/ * serving; } ;
struct pl08x_driver_data {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline void pl08x_put_phy_channel(struct pl08x_driver_data *pl08x,
					 struct pl08x_phy_chan *ch)
{
	ch->serving = NULL;
}