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
struct hostent {int /*<<< orphan*/  h_addr; } ;
struct TYPE_5__ {int page_scan_rep_mode; int page_scan_mode; int clock_offset; int /*<<< orphan*/  bdaddr; } ;
typedef  TYPE_1__ ng_hci_remote_name_req_cp ;
struct TYPE_6__ {int status; char* name; int /*<<< orphan*/  bdaddr; } ;
typedef  TYPE_2__ ng_hci_remote_name_req_compl_ep ;
struct TYPE_7__ {scalar_t__ event; } ;
typedef  TYPE_3__ ng_hci_event_pkt_t ;
typedef  int /*<<< orphan*/  cp ;
typedef  int /*<<< orphan*/  b ;

/* Variables and functions */
 int /*<<< orphan*/  EIO ; 
 scalar_t__ ERROR ; 
 int FAILED ; 
 scalar_t__ NG_HCI_EVENT_REMOTE_NAME_REQ_COMPL ; 
 int NG_HCI_MANDATORY_PAGE_SCAN_MODE ; 
 int /*<<< orphan*/  NG_HCI_OCF_REMOTE_NAME_REQ ; 
 int /*<<< orphan*/  NG_HCI_OGF_LINK_CONTROL ; 
 int /*<<< orphan*/  NG_HCI_OPCODE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int NG_HCI_SCAN_REP_MODE0 ; 
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
 int htole16 (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int sscanf (char*,char*,int*) ; 
 int /*<<< orphan*/  stdout ; 

__attribute__((used)) static int
hci_remote_name_request(int s, int argc, char **argv)
{
	int				 n0;
	char				 b[512];
	ng_hci_remote_name_req_cp	 cp;
	ng_hci_event_pkt_t		*e = (ng_hci_event_pkt_t *) b; 

	memset(&cp, 0, sizeof(cp));
	cp.page_scan_rep_mode = NG_HCI_SCAN_REP_MODE0;
	cp.page_scan_mode = NG_HCI_MANDATORY_PAGE_SCAN_MODE;

	/* parse command parameters */
	switch (argc) {
	case 4:
		/* clock_offset */
		if (sscanf(argv[3], "%x", &n0) != 1)
			return (USAGE);

		cp.clock_offset = (n0 & 0xffff);
		cp.clock_offset = htole16(cp.clock_offset);

	case 3:
		/* page_scan_mode */
		if (sscanf(argv[2], "%d", &n0) != 1 || n0 < 0x00 || n0 > 0x03)
			return (USAGE);

		cp.page_scan_mode = (n0 & 0xff);

	case 2:
		/* page_scan_rep_mode */
		if (sscanf(argv[1], "%d", &n0) != 1 || n0 < 0x00 || n0 > 0x02)
			return (USAGE);

		cp.page_scan_rep_mode = (n0 & 0xff);

	case 1:
		/* BD_ADDR */
		if (!bt_aton(argv[0], &cp.bdaddr)) {
			struct hostent	*he = NULL;

			if ((he = bt_gethostbyname(argv[0])) == NULL)
				return (USAGE);

			memcpy(&cp.bdaddr, he->h_addr, sizeof(cp.bdaddr));
		}
		break;

	default:
		return (USAGE);
	}

	/* send request and expect status response */
	n0 = sizeof(b);
	if (hci_request(s, NG_HCI_OPCODE(NG_HCI_OGF_LINK_CONTROL,
			NG_HCI_OCF_REMOTE_NAME_REQ),
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

	if (e->event == NG_HCI_EVENT_REMOTE_NAME_REQ_COMPL) {
		ng_hci_remote_name_req_compl_ep	*ep = 
				(ng_hci_remote_name_req_compl_ep *)(e + 1);

		if (ep->status != 0x00) {
			fprintf(stdout, "Status: %s [%#02x]\n", 
				hci_status2str(ep->status), ep->status);
			return (FAILED);
		}

		fprintf(stdout, "BD_ADDR: %s\n", hci_bdaddr2str(&ep->bdaddr));
		fprintf(stdout, "Name: %s\n", ep->name);
	} else 
		goto again;

	return (OK);
}