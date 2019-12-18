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
typedef  int /*<<< orphan*/  adapter_t ;

/* Variables and functions */
 int /*<<< orphan*/  VSC_REG (int,int,int) ; 
 int elmr_write (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int) ; 

int t3_vsc7323_set_mtu(adapter_t *adap, unsigned int mtu, int port)
{
	return elmr_write(adap, VSC_REG(1, port, 2), mtu);
}