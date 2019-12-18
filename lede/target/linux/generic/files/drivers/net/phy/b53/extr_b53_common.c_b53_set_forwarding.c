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
typedef  int /*<<< orphan*/  u8 ;
struct b53_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  B53_CTRL_PAGE ; 
 int /*<<< orphan*/  B53_SWITCH_MODE ; 
 int /*<<< orphan*/  SM_SW_FWD_EN ; 
 int /*<<< orphan*/  b53_read8 (struct b53_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  b53_write8 (struct b53_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void b53_set_forwarding(struct b53_device *dev, int enable)
{
	u8 mgmt;

	b53_read8(dev, B53_CTRL_PAGE, B53_SWITCH_MODE, &mgmt);

	if (enable)
		mgmt |= SM_SW_FWD_EN;
	else
		mgmt &= ~SM_SW_FWD_EN;

	b53_write8(dev, B53_CTRL_PAGE, B53_SWITCH_MODE, mgmt);
}