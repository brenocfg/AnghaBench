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
struct TYPE_3__ {int status; int /*<<< orphan*/  settings; int /*<<< orphan*/  con_handle; } ;
typedef  TYPE_1__ ng_hci_read_link_policy_settings_rp ;
struct TYPE_4__ {int /*<<< orphan*/  con_handle; } ;
typedef  TYPE_2__ ng_hci_read_link_policy_settings_cp ;
typedef  int /*<<< orphan*/  cp ;

/* Variables and functions */
 scalar_t__ ERROR ; 
 int FAILED ; 
 int /*<<< orphan*/  NG_HCI_OCF_READ_LINK_POLICY_SETTINGS ; 
 int /*<<< orphan*/  NG_HCI_OGF_LINK_POLICY ; 
 int /*<<< orphan*/  NG_HCI_OPCODE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int OK ; 
 int USAGE ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ hci_request (int,int /*<<< orphan*/ ,char const*,int,char*,int*) ; 
 char* hci_status2str (int) ; 
 int /*<<< orphan*/  htole16 (int /*<<< orphan*/ ) ; 
 int le16toh (int /*<<< orphan*/ ) ; 
 int sscanf (char*,char*,int*) ; 
 int /*<<< orphan*/  stdout ; 

__attribute__((used)) static int
hci_read_link_policy_settings(int s, int argc, char **argv)
{
	ng_hci_read_link_policy_settings_cp	cp;
	ng_hci_read_link_policy_settings_rp	rp;
	int					n;

	/* parse command parameters */
	switch (argc) {
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

	/* send request */
	n = sizeof(rp);
	if (hci_request(s, NG_HCI_OPCODE(NG_HCI_OGF_LINK_POLICY,
			NG_HCI_OCF_READ_LINK_POLICY_SETTINGS), 
			(char const *) &cp, sizeof(cp), 
			(char *) &rp, &n) == ERROR)
		return (ERROR);

	if (rp.status != 0x00) {
		fprintf(stdout, "Status: %s [%#02x]\n", 
			hci_status2str(rp.status), rp.status);
		return (FAILED);
	}

	fprintf(stdout, "Connection handle: %d\n", le16toh(rp.con_handle));
	fprintf(stdout, "Link policy settings: %#x\n", le16toh(rp.settings));

	return (OK);
}