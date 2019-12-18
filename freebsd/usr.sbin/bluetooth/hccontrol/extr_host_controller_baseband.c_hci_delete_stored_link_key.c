#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct hostent {int /*<<< orphan*/  h_addr; } ;
struct TYPE_4__ {int status; int num_keys_deleted; } ;
typedef  TYPE_1__ ng_hci_delete_stored_link_key_rp ;
struct TYPE_5__ {int delete_all; int /*<<< orphan*/  bdaddr; } ;
typedef  TYPE_2__ ng_hci_delete_stored_link_key_cp ;
typedef  int int32_t ;
typedef  int /*<<< orphan*/  cp ;

/* Variables and functions */
 scalar_t__ ERROR ; 
 int FAILED ; 
 int /*<<< orphan*/  NG_HCI_OCF_DELETE_STORED_LINK_KEY ; 
 int /*<<< orphan*/  NG_HCI_OGF_HC_BASEBAND ; 
 int /*<<< orphan*/  NG_HCI_OPCODE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int OK ; 
 int USAGE ; 
 int /*<<< orphan*/  bt_aton (char*,int /*<<< orphan*/ *) ; 
 struct hostent* bt_gethostbyname (char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ hci_request (int,int /*<<< orphan*/ ,char const*,int,char*,int*) ; 
 char* hci_status2str (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stdout ; 

__attribute__((used)) static int
hci_delete_stored_link_key(int s, int argc, char **argv)
{
	ng_hci_delete_stored_link_key_cp	cp;
	ng_hci_delete_stored_link_key_rp	rp;
	int32_t					n;

	memset(&cp, 0, sizeof(cp));

	switch (argc) {
	case 1:
		/* parse BD_ADDR */
		if (!bt_aton(argv[0], &cp.bdaddr)) {
			struct hostent	*he = NULL;

			if ((he = bt_gethostbyname(argv[0])) == NULL)
				return (USAGE);

			memcpy(&cp.bdaddr, he->h_addr, sizeof(cp.bdaddr));
		}
		break;

	default:
		cp.delete_all = 1;
		break;
	}

	/* send command */
	n = sizeof(cp);
	if (hci_request(s, NG_HCI_OPCODE(NG_HCI_OGF_HC_BASEBAND, 
			NG_HCI_OCF_DELETE_STORED_LINK_KEY),
			(char const *) &cp, sizeof(cp),
			(char *) &rp, &n) == ERROR)
		return (ERROR);

	if (rp.status != 0x00) {
		fprintf(stdout, "Status: %s [%#02x]\n", 
			hci_status2str(rp.status), rp.status);
		return (FAILED);
	}

	fprintf(stdout, "Number of keys deleted: %d\n", rp.num_keys_deleted);

	return (OK);
}