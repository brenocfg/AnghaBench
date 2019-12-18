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
 int /*<<< orphan*/  DEL_ADDR ; 
 int /*<<< orphan*/  etap_change (int /*<<< orphan*/ ,unsigned char*,unsigned char*,int) ; 

__attribute__((used)) static void etap_close_addr(unsigned char *addr, unsigned char *netmask,
			    void *arg)
{
	etap_change(DEL_ADDR, addr, netmask, *((int *) arg));
}