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
struct ng_btsocket_l2cap_raw_node_flags {int flags; } ;
typedef  int /*<<< orphan*/  r ;

/* Variables and functions */
 int ERROR ; 
 int NG_L2CAP_CLT_RFCOMM_DISABLED ; 
 int NG_L2CAP_CLT_SDP_DISABLED ; 
 int NG_L2CAP_CLT_TCP_DISABLED ; 
 int OK ; 
 int /*<<< orphan*/  SIOC_L2CAP_NODE_GET_FLAGS ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ ioctl (int,int /*<<< orphan*/ ,struct ng_btsocket_l2cap_raw_node_flags*,int) ; 
 int /*<<< orphan*/  memset (struct ng_btsocket_l2cap_raw_node_flags*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stdout ; 

__attribute__((used)) static int
l2cap_read_node_flags(int s, int argc, char **argv)
{
	struct ng_btsocket_l2cap_raw_node_flags	r;

	memset(&r, 0, sizeof(r));
	if (ioctl(s, SIOC_L2CAP_NODE_GET_FLAGS, &r, sizeof(r)) < 0)
		return (ERROR);

	fprintf(stdout, "Connectionless traffic flags:\n");
	fprintf(stdout, "\tSDP: %s\n",
		(r.flags & NG_L2CAP_CLT_SDP_DISABLED)? "disabled" : "enabled");
	fprintf(stdout, "\tRFCOMM: %s\n",
		(r.flags & NG_L2CAP_CLT_RFCOMM_DISABLED)? "disabled":"enabled");
	fprintf(stdout, "\tTCP: %s\n",
		(r.flags & NG_L2CAP_CLT_TCP_DISABLED)? "disabled" : "enabled");

	return (OK);
}