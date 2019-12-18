#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int /*<<< orphan*/  rp ;
struct TYPE_3__ {int status; } ;
typedef  TYPE_1__ ng_hci_write_page_timo_rp ;
struct TYPE_4__ {int /*<<< orphan*/  timeout; } ;
typedef  TYPE_2__ ng_hci_write_page_timo_cp ;
typedef  int /*<<< orphan*/  cp ;

/* Variables and functions */
 scalar_t__ ERROR ; 
 int FAILED ; 
 int /*<<< orphan*/  NG_HCI_OCF_WRITE_PAGE_TIMO ; 
 int /*<<< orphan*/  NG_HCI_OGF_HC_BASEBAND ; 
 int /*<<< orphan*/  NG_HCI_OPCODE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int OK ; 
 int USAGE ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,int) ; 
 scalar_t__ hci_request (int,int /*<<< orphan*/ ,char const*,int,char*,int*) ; 
 char* hci_status2str (int) ; 
 int /*<<< orphan*/  htole16 (int /*<<< orphan*/ ) ; 
 int sscanf (char*,char*,int*) ; 
 int /*<<< orphan*/  stdout ; 

__attribute__((used)) static int
hci_write_page_timeout(int s, int argc, char **argv)
{
	ng_hci_write_page_timo_cp	cp;
	ng_hci_write_page_timo_rp	rp;
	int				n;

	/* parse command parameters */
	switch (argc) {
	case 1:
		if (sscanf(argv[0], "%d", &n) != 1 || n < 1 || n > 0xffff)
			return (USAGE);

		cp.timeout = (uint16_t) n;
		cp.timeout = htole16(cp.timeout);
		break;

	default:
		return (USAGE);
	}

	/* send command */
	n = sizeof(rp);
	if (hci_request(s, NG_HCI_OPCODE(NG_HCI_OGF_HC_BASEBAND, 
			NG_HCI_OCF_WRITE_PAGE_TIMO),
			(char const *) &cp, sizeof(cp),
			(char *) &rp, &n) == ERROR)
		return (ERROR);

	if (rp.status != 0x00) {
		fprintf(stdout, "Status: %s [%#02x]\n", 
			hci_status2str(rp.status), rp.status);
		return (FAILED);
	}

	return (OK);
}