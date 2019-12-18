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
 int /*<<< orphan*/  mdioproxy_rendezvous_callback ; 
 int /*<<< orphan*/  rendezvous_register_target (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mdioproxy_attach(device_t dev)
{

	rendezvous_register_target(dev, mdioproxy_rendezvous_callback);
	return (bus_generic_attach(dev));
}