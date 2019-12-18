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
struct etherswitch_phyreg {int phy; int reg; int val; } ;
struct cfg {int /*<<< orphan*/  fd; } ;

/* Variables and functions */
 int /*<<< orphan*/  EX_OSERR ; 
 int /*<<< orphan*/  IOETHERSWITCHGETPHYREG ; 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct etherswitch_phyreg*) ; 

__attribute__((used)) static int
read_phyregister(struct cfg *cfg, int phy, int reg)
{
	struct etherswitch_phyreg er;
	
	er.phy = phy;
	er.reg = reg;
	if (ioctl(cfg->fd, IOETHERSWITCHGETPHYREG, &er) != 0)
		err(EX_OSERR, "ioctl(IOETHERSWITCHGETPHYREG)");
	return (er.val);
}