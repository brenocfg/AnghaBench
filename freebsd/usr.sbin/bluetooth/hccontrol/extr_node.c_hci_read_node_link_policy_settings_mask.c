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
struct ng_btsocket_hci_raw_node_link_policy_mask {int policy_mask; } ;
typedef  int /*<<< orphan*/  r ;

/* Variables and functions */
 int ERROR ; 
 int OK ; 
 int /*<<< orphan*/  SIOC_HCI_RAW_NODE_GET_LINK_POLICY_MASK ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ ioctl (int,int /*<<< orphan*/ ,struct ng_btsocket_hci_raw_node_link_policy_mask*,int) ; 
 int /*<<< orphan*/  memset (struct ng_btsocket_hci_raw_node_link_policy_mask*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stdout ; 

int
hci_read_node_link_policy_settings_mask(int s, int argc, char **argv)
{
	struct ng_btsocket_hci_raw_node_link_policy_mask	r;

	memset(&r, 0, sizeof(r));
	if (ioctl(s, SIOC_HCI_RAW_NODE_GET_LINK_POLICY_MASK, &r, sizeof(r)) < 0)
		return (ERROR);

	fprintf(stdout, "Link Policy Settings mask: %#04x\n", r.policy_mask);

	return (OK);
}