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
 int /*<<< orphan*/  EVENTHANDLER_DEREGISTER (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_clone ; 
 int /*<<< orphan*/ * mixer_ehtag ; 

__attribute__((used)) static void
mixer_sysuninit(void *p)
{
	if (mixer_ehtag == NULL)
		return;
	EVENTHANDLER_DEREGISTER(dev_clone, mixer_ehtag);
	mixer_ehtag = NULL;
}