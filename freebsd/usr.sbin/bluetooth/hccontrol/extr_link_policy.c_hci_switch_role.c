#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct hostent {int /*<<< orphan*/  h_addr; } ;
struct TYPE_4__ {int role; int /*<<< orphan*/  bdaddr; } ;
typedef  TYPE_1__ ng_hci_switch_role_cp ;
struct TYPE_5__ {int status; int role; int /*<<< orphan*/  bdaddr; } ;
typedef  TYPE_2__ ng_hci_role_change_ep ;
struct TYPE_6__ {scalar_t__ event; } ;
typedef  TYPE_3__ ng_hci_event_pkt_t ;
typedef  int /*<<< orphan*/  cp ;
typedef  int /*<<< orphan*/  b ;

/* Variables and functions */
 int /*<<< orphan*/  EIO ; 
 scalar_t__ ERROR ; 
 int FAILED ; 
 scalar_t__ NG_HCI_EVENT_ROLE_CHANGE ; 
 int /*<<< orphan*/  NG_HCI_OCF_SWITCH_ROLE ; 
 int /*<<< orphan*/  NG_HCI_OGF_LINK_POLICY ; 
 int /*<<< orphan*/  NG_HCI_OPCODE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int NG_HCI_ROLE_MASTER ; 
 int NG_HCI_ROLE_SLAVE ; 
 int OK ; 
 int USAGE ; 
 int /*<<< orphan*/  bt_aton (char*,int /*<<< orphan*/ *) ; 
 struct hostent* bt_gethostbyname (char*) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,...) ; 
 char* hci_bdaddr2str (int /*<<< orphan*/ *) ; 
 scalar_t__ hci_recv (int,char*,int*) ; 
 scalar_t__ hci_request (int,int /*<<< orphan*/ ,char const*,int,char*,int*) ; 
 char* hci_status2str (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int sscanf (char*,char*,int*) ; 
 int /*<<< orphan*/  stdout ; 

__attribute__((used)) static int
hci_switch_role(int s, int argc, char **argv)
{
	int			 n0;
	char			 b[512];
	ng_hci_switch_role_cp	 cp;
	ng_hci_event_pkt_t	*e = (ng_hci_event_pkt_t *) b; 

	/* parse command parameters */
	switch (argc) {
	case 2:
		/* bdaddr */
		if (!bt_aton(argv[0], &cp.bdaddr)) {
			struct hostent	*he = NULL;

			if ((he = bt_gethostbyname(argv[0])) == NULL)
				return (USAGE);

			memcpy(&cp.bdaddr, he->h_addr, sizeof(cp.bdaddr));
		}

		/* role */
		if (sscanf(argv[1], "%d", &n0) != 1)
			return (USAGE);

		cp.role = n0? NG_HCI_ROLE_SLAVE : NG_HCI_ROLE_MASTER;
		break;

	default:
		return (USAGE);
	}

	/* send request and expect status response */
	n0 = sizeof(b);
	if (hci_request(s, NG_HCI_OPCODE(NG_HCI_OGF_LINK_POLICY,
			NG_HCI_OCF_SWITCH_ROLE),
			(char const *) &cp, sizeof(cp), b, &n0) == ERROR)
		return (ERROR);

	if (*b != 0x00)
		return (FAILED);

	/* wait for event */
again:
	n0 = sizeof(b);
	if (hci_recv(s, b, &n0) == ERROR)
		return (ERROR);
	if (n0 < sizeof(*e)) {
		errno = EIO;
		return (ERROR);
	}

	if (e->event == NG_HCI_EVENT_ROLE_CHANGE) {
		ng_hci_role_change_ep	*ep = (ng_hci_role_change_ep *)(e + 1);

		if (ep->status != 0x00) {
			fprintf(stdout, "Status: %s [%#02x]\n", 
				hci_status2str(ep->status), ep->status);
			return (FAILED);
		}

		fprintf(stdout, "BD_ADDR: %s\n", hci_bdaddr2str(&ep->bdaddr));
		fprintf(stdout, "Role: %s [%#x]\n",
			(ep->role == NG_HCI_ROLE_MASTER)? "Master" : "Slave",
			ep->role);
	} else
		goto again;

	return (OK);
}