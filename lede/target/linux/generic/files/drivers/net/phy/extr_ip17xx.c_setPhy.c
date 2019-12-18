#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct ip17xx_state {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  m; int /*<<< orphan*/  p; } ;
typedef  TYPE_1__ reg ;

/* Variables and functions */
 int EFAULT ; 
 int /*<<< orphan*/  REG_SUPP (TYPE_1__) ; 
 int /*<<< orphan*/  getPhy (struct ip17xx_state*,TYPE_1__) ; 
 int ip_phy_write (struct ip17xx_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mdelay (int) ; 

__attribute__((used)) static int setPhy(struct ip17xx_state *state, reg mii, u16 value)
{
	int err;

	if (!REG_SUPP(mii))
		return -EFAULT;
	err = ip_phy_write(state, mii.p, mii.m, value);
	if (err < 0)
		return err;
	mdelay(2);
	getPhy(state, mii);
	return 0;
}