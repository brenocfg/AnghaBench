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
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int bus_generic_attach (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
miiproxy_attach(device_t dev)
{

	/*
	 * The ethernet interface needs to call mii_attach_proxy() to pass
	 * the relevant parameters for rendezvous with the MDIO target.
	 */
	return (bus_generic_attach(dev));
}