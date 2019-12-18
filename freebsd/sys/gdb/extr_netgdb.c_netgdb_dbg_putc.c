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

/* Variables and functions */
 int /*<<< orphan*/  netgdb_dbg_sendpacket (char*,int) ; 

__attribute__((used)) static void
netgdb_dbg_putc(int i)
{
	char c;

	c = i;
	netgdb_dbg_sendpacket(&c, 1);

}