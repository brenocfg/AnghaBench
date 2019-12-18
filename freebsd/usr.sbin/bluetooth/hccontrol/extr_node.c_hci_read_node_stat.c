#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int cmd_sent; int evnt_recv; int acl_recv; int acl_sent; int sco_recv; int sco_sent; int bytes_recv; int bytes_sent; } ;
struct ng_btsocket_hci_raw_node_stat {TYPE_1__ stat; } ;
typedef  int /*<<< orphan*/  r ;

/* Variables and functions */
 int ERROR ; 
 int OK ; 
 int /*<<< orphan*/  SIOC_HCI_RAW_NODE_GET_STAT ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ ioctl (int,int /*<<< orphan*/ ,struct ng_btsocket_hci_raw_node_stat*,int) ; 
 int /*<<< orphan*/  memset (struct ng_btsocket_hci_raw_node_stat*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stdout ; 

__attribute__((used)) static int
hci_read_node_stat(int s, int argc, char **argv)
{
	struct ng_btsocket_hci_raw_node_stat	r;

	memset(&r, 0, sizeof(r));
	if (ioctl(s, SIOC_HCI_RAW_NODE_GET_STAT, &r, sizeof(r)) < 0)
		return (ERROR);

	fprintf(stdout, "Commands sent: %d\n", r.stat.cmd_sent);
	fprintf(stdout, "Events received: %d\n", r.stat.evnt_recv);
	fprintf(stdout, "ACL packets received: %d\n", r.stat.acl_recv);
	fprintf(stdout, "ACL packets sent: %d\n", r.stat.acl_sent);
	fprintf(stdout, "SCO packets received: %d\n", r.stat.sco_recv);
	fprintf(stdout, "SCO packets sent: %d\n", r.stat.sco_sent);
	fprintf(stdout, "Bytes received: %d\n", r.stat.bytes_recv);
	fprintf(stdout, "Bytes sent: %d\n", r.stat.bytes_sent);

	return (OK);
}