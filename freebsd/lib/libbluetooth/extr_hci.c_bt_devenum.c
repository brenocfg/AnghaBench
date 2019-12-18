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
struct sockaddr_hci {int hci_len; char* hci_node; int /*<<< orphan*/  hci_family; } ;
struct sockaddr {int dummy; } ;
struct nodeinfo {int /*<<< orphan*/  name; } ;
struct ng_btsocket_hci_raw_node_list_names {int num_names; struct nodeinfo* names; } ;
struct bt_devinfo {char* devname; } ;
typedef  int /*<<< orphan*/  rp ;
typedef  int /*<<< orphan*/  ha ;
typedef  scalar_t__ (* bt_devenum_cb_t ) (int,struct bt_devinfo*,void*) ;

/* Variables and functions */
 int /*<<< orphan*/  AF_BLUETOOTH ; 
 int /*<<< orphan*/  BLUETOOTH_PROTO_HCI ; 
 int /*<<< orphan*/  ENOMEM ; 
 int HCI_DEVMAX ; 
 int /*<<< orphan*/  PF_BLUETOOTH ; 
 int /*<<< orphan*/  SIOC_HCI_RAW_NODE_LIST_NAMES ; 
 int /*<<< orphan*/  SOCK_RAW ; 
 scalar_t__ bind (int,struct sockaddr*,int) ; 
 scalar_t__ bt_devinfo (struct bt_devinfo*) ; 
 scalar_t__ calloc (int,int) ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ connect (int,struct sockaddr*,int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  free (struct nodeinfo*) ; 
 scalar_t__ ioctl (int,int /*<<< orphan*/ ,struct ng_btsocket_hci_raw_node_list_names*,int) ; 
 int /*<<< orphan*/  memset (struct sockaddr_hci*,int /*<<< orphan*/ ,int) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcpy (char*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ stub1 (int,struct bt_devinfo*,void*) ; 

int
bt_devenum(bt_devenum_cb_t cb, void *arg)
{
	struct ng_btsocket_hci_raw_node_list_names	rp;
	struct bt_devinfo				di;
	struct sockaddr_hci				ha;
	int						s, i, count;

	rp.num_names = HCI_DEVMAX;
	rp.names = (struct nodeinfo *) calloc(rp.num_names,
						sizeof(struct nodeinfo));
	if (rp.names == NULL) {
		errno = ENOMEM;
		return (-1);
	}

	memset(&ha, 0, sizeof(ha));
	ha.hci_len = sizeof(ha);
	ha.hci_family = AF_BLUETOOTH;
	ha.hci_node[0] = 'x';

	s = socket(PF_BLUETOOTH, SOCK_RAW, BLUETOOTH_PROTO_HCI);
	if (s < 0) {
		free(rp.names);

		return (-1);
	}

	if (bind(s, (struct sockaddr *) &ha, sizeof(ha)) < 0 ||
	    connect(s, (struct sockaddr *) &ha, sizeof(ha)) < 0 ||
	    ioctl(s, SIOC_HCI_RAW_NODE_LIST_NAMES, &rp, sizeof(rp)) < 0) {
		close(s);
		free(rp.names);

		return (-1);
	}

	for (count = 0, i = 0; i < rp.num_names; i ++) {
		strlcpy(di.devname, rp.names[i].name, sizeof(di.devname));
		if (bt_devinfo(&di) < 0)
			continue;

		count ++;

		if (cb == NULL)
			continue;

		strlcpy(ha.hci_node, rp.names[i].name, sizeof(ha.hci_node));
		if (bind(s, (struct sockaddr *) &ha, sizeof(ha)) < 0 ||
		    connect(s, (struct sockaddr *) &ha, sizeof(ha)) < 0)
			continue;

		if ((*cb)(s, &di, arg) > 0)
			break;
	}

	close (s);
	free(rp.names);

	return (count);
}