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
struct nuport_mac_priv {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int HZ ; 
 int /*<<< orphan*/  MII_ADDR_REG ; 
 int MII_BUSY ; 
 int /*<<< orphan*/  cpu_relax () ; 
 int jiffies ; 
 int nuport_mac_readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  time_after_eq (unsigned long,unsigned long) ; 

__attribute__((used)) static inline int nuport_mac_mii_busy_wait(struct nuport_mac_priv *priv)
{
	unsigned long curr;
	unsigned long finish = jiffies + 3 * HZ;

	do {
		curr = jiffies;
		if (!(nuport_mac_readl(MII_ADDR_REG) & MII_BUSY))
			return 0;
		cpu_relax();
	} while (!time_after_eq(curr, finish));

	return -EBUSY;
}