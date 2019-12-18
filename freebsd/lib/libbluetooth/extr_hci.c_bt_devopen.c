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
typedef  int /*<<< orphan*/  ha ;
typedef  int /*<<< orphan*/  bdaddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  AF_BLUETOOTH ; 
 int /*<<< orphan*/  BLUETOOTH_PROTO_HCI ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENXIO ; 
 int /*<<< orphan*/  PF_BLUETOOTH ; 
 int /*<<< orphan*/  SOCK_RAW ; 
 scalar_t__ bind (int,struct sockaddr*,int) ; 
 scalar_t__ bt_aton (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * bt_dev2node (char const*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bt_devname (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ connect (int,struct sockaddr*,int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  memset (struct sockaddr_hci*,int /*<<< orphan*/ ,int) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
bt_devopen(char const *devname)
{
	struct sockaddr_hci	ha;
	bdaddr_t		ba;
	int			s;

	if (devname == NULL) {
		errno = EINVAL;
		return (-1);
	}

	memset(&ha, 0, sizeof(ha));
	ha.hci_len = sizeof(ha);
	ha.hci_family = AF_BLUETOOTH;

	if (bt_aton(devname, &ba)) {
		if (!bt_devname(ha.hci_node, &ba))
			return (-1);
	} else if (bt_dev2node(devname, ha.hci_node,
					sizeof(ha.hci_node)) == NULL) {
		errno = ENXIO;
		return (-1);
	}

	s = socket(PF_BLUETOOTH, SOCK_RAW, BLUETOOTH_PROTO_HCI);
	if (s < 0)
		return (-1);

	if (bind(s, (struct sockaddr *) &ha, sizeof(ha)) < 0 ||
	    connect(s, (struct sockaddr *) &ha, sizeof(ha)) < 0) {
		close(s);
		return (-1);
	}

	return (s);
}