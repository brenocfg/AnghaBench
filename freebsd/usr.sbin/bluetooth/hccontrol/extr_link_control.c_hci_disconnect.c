#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_5__ {scalar_t__ event; } ;
typedef  TYPE_1__ ng_hci_event_pkt_t ;
struct TYPE_6__ {int reason; int /*<<< orphan*/  con_handle; } ;
typedef  TYPE_2__ ng_hci_discon_cp ;
struct TYPE_7__ {int status; int reason; int /*<<< orphan*/  con_handle; } ;
typedef  TYPE_3__ ng_hci_discon_compl_ep ;
typedef  int /*<<< orphan*/  cp ;
typedef  int /*<<< orphan*/  b ;

/* Variables and functions */
 int /*<<< orphan*/  EIO ; 
 scalar_t__ ERROR ; 
 int FAILED ; 
 scalar_t__ NG_HCI_EVENT_DISCON_COMPL ; 
 int /*<<< orphan*/  NG_HCI_OCF_DISCON ; 
 int /*<<< orphan*/  NG_HCI_OGF_LINK_CONTROL ; 
 int /*<<< orphan*/  NG_HCI_OPCODE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int OK ; 
 int USAGE ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ hci_recv (int,char*,int*) ; 
 scalar_t__ hci_request (int,int /*<<< orphan*/ ,char const*,int,char*,int*) ; 
 char* hci_status2str (int) ; 
 int /*<<< orphan*/  htole16 (int /*<<< orphan*/ ) ; 
 int le16toh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int sscanf (char*,char*,int*) ; 
 int /*<<< orphan*/  stdout ; 

__attribute__((used)) static int
hci_disconnect(int s, int argc, char **argv)
{
	int			 n;
	char			 b[512];
	ng_hci_discon_cp	 cp;
	ng_hci_event_pkt_t	*e = (ng_hci_event_pkt_t *) b; 

	/* Set defaults */
	memset(&cp, 0, sizeof(cp));
	cp.reason = 0x13;

	/* parse command parameters */
	switch (argc) {
	case 2:
		/* reason */
		if (sscanf(argv[1], "%d", &n) != 1 || n <= 0x00 || n > 0xff)
			return (USAGE);

		cp.reason = (uint8_t) (n & 0xff);

	case 1:
		/* connection handle */
		if (sscanf(argv[0], "%d", &n) != 1 || n <= 0 || n > 0x0eff)
			return (USAGE);

		cp.con_handle = (uint16_t) (n & 0x0fff);
		cp.con_handle = htole16(cp.con_handle);
		break;

	default:
		return (USAGE);
	}

	/* send request and expect status response */
	n = sizeof(b);
	if (hci_request(s, NG_HCI_OPCODE(NG_HCI_OGF_LINK_CONTROL,
			NG_HCI_OCF_DISCON),
			(char const *) &cp, sizeof(cp), b, &n) == ERROR)
		return (ERROR);

	if (*b != 0x00)
		return (FAILED);

	/* wait for event */
again:
	n = sizeof(b);
	if (hci_recv(s, b, &n) == ERROR)
		return (ERROR);
	if (n < sizeof(*e)) {
		errno = EIO;
		return (ERROR);
	}

	if (e->event == NG_HCI_EVENT_DISCON_COMPL) {
		ng_hci_discon_compl_ep	*ep = (ng_hci_discon_compl_ep *)(e + 1);

		if (ep->status != 0x00) {
			fprintf(stdout, "Status: %s [%#02x]\n", 
				hci_status2str(ep->status), ep->status);
			return (FAILED);
		}

		fprintf(stdout, "Connection handle: %d\n",
			le16toh(ep->con_handle));
		fprintf(stdout, "Reason: %s [%#02x]\n",
			hci_status2str(ep->reason), ep->reason);
	} else
		goto again;

	return (OK);
}