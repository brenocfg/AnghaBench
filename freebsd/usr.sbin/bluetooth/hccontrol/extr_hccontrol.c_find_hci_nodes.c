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
struct sockaddr_hci {int hci_len; int /*<<< orphan*/  hci_node; int /*<<< orphan*/  hci_family; } ;
struct sockaddr {int dummy; } ;
struct nodeinfo {int dummy; } ;
struct ng_btsocket_hci_raw_node_list_names {int num_names; struct nodeinfo* names; } ;
typedef  int /*<<< orphan*/  r ;
typedef  int /*<<< orphan*/  addr ;

/* Variables and functions */
 int /*<<< orphan*/  AF_BLUETOOTH ; 
 int /*<<< orphan*/  BLUETOOTH_PROTO_HCI ; 
 int MAX_NODE_NUM ; 
 int /*<<< orphan*/  PF_BLUETOOTH ; 
 int /*<<< orphan*/  SIOC_HCI_RAW_NODE_LIST_NAMES ; 
 int /*<<< orphan*/  SOCK_RAW ; 
 scalar_t__ bind (int,struct sockaddr*,int) ; 
 scalar_t__ calloc (int,int) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 scalar_t__ ioctl (int,int /*<<< orphan*/ ,struct ng_btsocket_hci_raw_node_list_names*,int) ; 
 int /*<<< orphan*/  memset (struct sockaddr_hci*,int /*<<< orphan*/ ,int) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,char const*,int) ; 

__attribute__((used)) static int
find_hci_nodes(struct nodeinfo** nodes)
{
	struct ng_btsocket_hci_raw_node_list_names	r;
	struct sockaddr_hci				addr;
	int						s;
	const char *					node = "ubt0hci";

	r.num_names = MAX_NODE_NUM;
	r.names = (struct nodeinfo*)calloc(MAX_NODE_NUM, sizeof(struct nodeinfo));
	if (r.names == NULL)
		err(8, "Could not allocate memory");

	s = socket(PF_BLUETOOTH, SOCK_RAW, BLUETOOTH_PROTO_HCI);
	if (s < 0)
		err(9, "Could not create socket");

	memset(&addr, 0, sizeof(addr));
	addr.hci_len = sizeof(addr);
	addr.hci_family = AF_BLUETOOTH;
	strncpy(addr.hci_node, node, sizeof(addr.hci_node));
	if (bind(s, (struct sockaddr *) &addr, sizeof(addr)) < 0)
		err(10, "Could not bind socket");

	if (ioctl(s, SIOC_HCI_RAW_NODE_LIST_NAMES, &r, sizeof(r)) < 0)
		err(11, "Could not get list of HCI nodes");

	close(s);

	*nodes = r.names;

	return (r.num_names);
}