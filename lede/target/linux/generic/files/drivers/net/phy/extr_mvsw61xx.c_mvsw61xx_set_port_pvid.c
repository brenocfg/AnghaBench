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
typedef  scalar_t__ u16 ;
struct switch_dev {int dummy; } ;
struct mvsw61xx_state {TYPE_1__* ports; } ;
struct TYPE_2__ {scalar_t__ pvid; } ;

/* Variables and functions */
 int EINVAL ; 
 int MV_VLANS ; 
 struct mvsw61xx_state* get_state (struct switch_dev*) ; 

__attribute__((used)) static int
mvsw61xx_set_port_pvid(struct switch_dev *dev, int port, int val)
{
	struct mvsw61xx_state *state = get_state(dev);

	if (val < 0 || val >= MV_VLANS)
		return -EINVAL;

	state->ports[port].pvid = (u16)val;

	return 0;
}