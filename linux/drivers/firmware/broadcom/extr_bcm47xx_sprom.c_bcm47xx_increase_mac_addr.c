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
typedef  int u8 ;

/* Variables and functions */
 int ENOENT ; 
 int ETH_ALEN ; 
 int /*<<< orphan*/  pr_err (char*) ; 

__attribute__((used)) static int bcm47xx_increase_mac_addr(u8 *mac, u8 num)
{
	u8 *oui = mac + ETH_ALEN/2 - 1;
	u8 *p = mac + ETH_ALEN - 1;

	do {
		(*p) += num;
		if (*p > num)
			break;
		p--;
		num = 1;
	} while (p != oui);

	if (p == oui) {
		pr_err("unable to fetch mac address\n");
		return -ENOENT;
	}
	return 0;
}