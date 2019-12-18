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
typedef  scalar_t__ uint32_t ;
struct ctl_nexus {int targ_port; scalar_t__ initid; } ;

/* Variables and functions */
 int CTL_MAX_INIT_PER_PORT ; 

uint32_t
ctl_get_initindex(struct ctl_nexus *nexus)
{
	return (nexus->initid + (nexus->targ_port * CTL_MAX_INIT_PER_PORT));
}