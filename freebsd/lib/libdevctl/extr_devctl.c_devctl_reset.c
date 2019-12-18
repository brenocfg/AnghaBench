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
 int /*<<< orphan*/  DEVF_RESET_DETACH ; 
 int /*<<< orphan*/  DEV_RESET ; 
 int devctl_simple_request (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 

int
devctl_reset(const char *device, bool detach)
{

	return (devctl_simple_request(DEV_RESET, device, detach ?
	    DEVF_RESET_DETACH : 0));
}