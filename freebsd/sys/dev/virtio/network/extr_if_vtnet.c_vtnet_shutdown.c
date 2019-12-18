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
 int vtnet_suspend (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
vtnet_shutdown(device_t dev)
{

	/*
	 * Suspend already does all of what we need to
	 * do here; we just never expect to be resumed.
	 */
	return (vtnet_suspend(dev));
}