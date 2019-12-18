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
struct switch_dev {int dummy; } ;
struct rtl_phyregs {int /*<<< orphan*/  duplex; int /*<<< orphan*/  speed; int /*<<< orphan*/  nway; } ;

/* Variables and functions */
 int /*<<< orphan*/  DUPLEX ; 
 int /*<<< orphan*/  NWAY ; 
 int /*<<< orphan*/  RTL_PORT_REG (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SPEED ; 
 int /*<<< orphan*/  rtl_set (struct switch_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
rtl_phy_restore(struct switch_dev *dev, int port, struct rtl_phyregs *regs)
{
	rtl_set(dev, RTL_PORT_REG(port, NWAY), regs->nway);
	rtl_set(dev, RTL_PORT_REG(port, SPEED), regs->speed);
	rtl_set(dev, RTL_PORT_REG(port, DUPLEX), regs->duplex);
}