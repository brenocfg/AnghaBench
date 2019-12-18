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
struct slip_data {scalar_t__ slave; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  open_addr (unsigned char*,unsigned char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void slip_add_addr(unsigned char *addr, unsigned char *netmask,
			  void *data)
{
	struct slip_data *pri = data;

	if (pri->slave < 0)
		return;
	open_addr(addr, netmask, pri->name);
}