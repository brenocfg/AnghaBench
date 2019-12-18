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
typedef  int /*<<< orphan*/  if_ctx_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  device_get_softc (int /*<<< orphan*/ ) ; 
 int iflib_device_deregister (int /*<<< orphan*/ ) ; 

int
iflib_device_detach(device_t dev)
{
	if_ctx_t ctx = device_get_softc(dev);

	return (iflib_device_deregister(ctx));
}