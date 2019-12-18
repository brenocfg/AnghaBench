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
struct ng_btsocket_hci_raw_node_bdaddr {int /*<<< orphan*/  bdaddr; } ;
typedef  int /*<<< orphan*/  r ;

/* Variables and functions */
 int ERROR ; 
 int OK ; 
 int /*<<< orphan*/  SIOC_HCI_RAW_NODE_GET_BDADDR ; 
 char* bt_ntoa (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 scalar_t__ ioctl (int,int /*<<< orphan*/ ,struct ng_btsocket_hci_raw_node_bdaddr*,int) ; 
 int /*<<< orphan*/  memset (struct ng_btsocket_hci_raw_node_bdaddr*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stdout ; 

__attribute__((used)) static int
hci_read_node_bd_addr(int s, int argc, char **argv)
{
	struct ng_btsocket_hci_raw_node_bdaddr	r;

	memset(&r, 0, sizeof(r));
	if (ioctl(s, SIOC_HCI_RAW_NODE_GET_BDADDR, &r, sizeof(r)) < 0)
		return (ERROR);

	fprintf(stdout, "BD_ADDR: %s\n", bt_ntoa(&r.bdaddr, NULL));

	return (OK);
}