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
 int ERROR ; 
 int OK ; 
 int /*<<< orphan*/  SIOC_HCI_RAW_NODE_RESET_STAT ; 
 scalar_t__ ioctl (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
hci_reset_node_stat(int s, int argc, char **argv)
{
	if (ioctl(s, SIOC_HCI_RAW_NODE_RESET_STAT) < 0)
		return (ERROR);

	return (OK);
}