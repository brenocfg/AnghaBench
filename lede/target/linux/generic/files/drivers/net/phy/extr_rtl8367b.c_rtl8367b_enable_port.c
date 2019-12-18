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
struct rtl8366_smi {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  REG_WR (struct rtl8366_smi*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RTL8367B_PORTS_ALL ; 
 int /*<<< orphan*/  RTL8367B_PORT_ISOLATION_REG (int) ; 

__attribute__((used)) static int rtl8367b_enable_port(struct rtl8366_smi *smi, int port, int enable)
{
	int err;

	REG_WR(smi, RTL8367B_PORT_ISOLATION_REG(port),
	       (enable) ? RTL8367B_PORTS_ALL : 0);

	return 0;
}