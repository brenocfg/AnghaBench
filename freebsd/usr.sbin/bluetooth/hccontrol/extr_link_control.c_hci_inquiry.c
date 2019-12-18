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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_4__ {int num_responses; } ;
typedef  TYPE_1__ ng_hci_inquiry_result_ep ;
struct TYPE_5__ {int* lap; int inquiry_length; int num_responses; } ;
typedef  TYPE_2__ ng_hci_inquiry_cp ;
struct TYPE_6__ {int event; } ;
typedef  TYPE_3__ ng_hci_event_pkt_t ;
typedef  int /*<<< orphan*/  cp ;
typedef  int /*<<< orphan*/  b ;

/* Variables and functions */
 int /*<<< orphan*/  EIO ; 
 scalar_t__ ERROR ; 
 int FAILED ; 
#define  NG_HCI_EVENT_INQUIRY_COMPL 129 
#define  NG_HCI_EVENT_INQUIRY_RESULT 128 
 int /*<<< orphan*/  NG_HCI_OCF_INQUIRY ; 
 int /*<<< orphan*/  NG_HCI_OGF_LINK_CONTROL ; 
 int /*<<< orphan*/  NG_HCI_OPCODE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int OK ; 
 int USAGE ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  hci_inquiry_response (int,int /*<<< orphan*/ **) ; 
 scalar_t__ hci_recv (int,char*,int*) ; 
 scalar_t__ hci_request (int,int /*<<< orphan*/ ,char const*,int,char*,int*) ; 
 char* hci_status2str (char) ; 
 int sscanf (char*,char*,int*,...) ; 
 int /*<<< orphan*/  stdout ; 
 int timeout ; 

__attribute__((used)) static int
hci_inquiry(int s, int argc, char **argv)
{
	int			 n0, n1, n2, timo;
	char			 b[512];
	ng_hci_inquiry_cp	 cp;
	ng_hci_event_pkt_t	*e = (ng_hci_event_pkt_t *) b;

	/* set defaults */
	cp.lap[2] = 0x9e;
	cp.lap[1] = 0x8b;
	cp.lap[0] = 0x33;
	cp.inquiry_length = 5;
	cp.num_responses = 8;

	/* parse command parameters */
	switch (argc) {
	case 3:
		/* number of responses, range 0x00 - 0xff */
		if (sscanf(argv[2], "%d", &n0) != 1 || n0 < 0 || n0 > 0xff)
			return (USAGE);

		cp.num_responses = (n0 & 0xff);

	case 2:
		/* inquiry length (N * 1.28) sec, range 0x01 - 0x30 */
		if (sscanf(argv[1], "%d", &n0) != 1 || n0 < 0x1 || n0 > 0x30)
			return (USAGE);

		cp.inquiry_length = (n0 & 0xff);

	case 1:
		/* LAP */
		if (sscanf(argv[0], "%x:%x:%x", &n2, &n1, &n0) != 3)
			return (USAGE);

		cp.lap[0] = (n0 & 0xff);
		cp.lap[1] = (n1 & 0xff);
		cp.lap[2] = (n2 & 0xff);

	case 0:
		/* use defaults */
		break;

	default:
		return (USAGE);
	}

	/* send request and expect status back */
	n0 = sizeof(b);
	if (hci_request(s, NG_HCI_OPCODE(NG_HCI_OGF_LINK_CONTROL,
			NG_HCI_OCF_INQUIRY), (char const *) &cp, sizeof(cp),
			b, &n0) == ERROR)
		return (ERROR);

	if (*b != 0x00)
		return (FAILED);

	timo = timeout;
	timeout = cp.inquiry_length * 1.28 + 1;

wait_for_more:
	/* wait for inquiry events */
	n0 = sizeof(b);
	if (hci_recv(s, b, &n0) == ERROR) {
		timeout = timo;
		return (ERROR);
	}

	if (n0 < sizeof(*e)) {
		timeout = timo;
		errno = EIO;
		return (ERROR);
	}

	switch (e->event) {
	case NG_HCI_EVENT_INQUIRY_RESULT: {
		ng_hci_inquiry_result_ep	*ir = 
				(ng_hci_inquiry_result_ep *)(e + 1);
		uint8_t				*r = (uint8_t *)(ir + 1);

		fprintf(stdout, "Inquiry result, num_responses=%d\n",
			ir->num_responses);

		for (n0 = 0; n0 < ir->num_responses; n0++)
			hci_inquiry_response(n0, &r);

		goto wait_for_more;
		}

	case NG_HCI_EVENT_INQUIRY_COMPL:
		fprintf(stdout, "Inquiry complete. Status: %s [%#02x]\n",
			hci_status2str(*(b + sizeof(*e))), *(b + sizeof(*e)));
		break;

	default:
		goto wait_for_more;
	}

	timeout = timo;

	return (OK);
}