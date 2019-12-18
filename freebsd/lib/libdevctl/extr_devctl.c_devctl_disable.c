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
 int /*<<< orphan*/  DEVF_FORCE_DETACH ; 
 int /*<<< orphan*/  DEV_DISABLE ; 
 int devctl_simple_request (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 

int
devctl_disable(const char *device, bool force_detach)
{

	return (devctl_simple_request(DEV_DISABLE, device, force_detach ?
	    DEVF_FORCE_DETACH : 0));
}