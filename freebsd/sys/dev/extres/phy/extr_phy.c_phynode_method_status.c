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
struct phynode {int dummy; } ;

/* Variables and functions */
 int PHY_STATUS_ENABLED ; 

__attribute__((used)) static int
phynode_method_status(struct phynode *phynode, int *status)
{
	*status = PHY_STATUS_ENABLED;
	return (0);
}