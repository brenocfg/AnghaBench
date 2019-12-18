#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  rp ;
struct TYPE_2__ {int status; int manufacturer; int hci_version; int hci_revision; int lmp_version; int lmp_subversion; } ;
typedef  TYPE_1__ ng_hci_read_local_ver_rp ;

/* Variables and functions */
 scalar_t__ ERROR ; 
 int FAILED ; 
 int /*<<< orphan*/  NG_HCI_OCF_READ_LOCAL_VER ; 
 int /*<<< orphan*/  NG_HCI_OGF_INFO ; 
 int /*<<< orphan*/  NG_HCI_OPCODE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int OK ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 char* hci_lmpver2str (int) ; 
 char* hci_manufacturer2str (int) ; 
 scalar_t__ hci_simple_request (int,int /*<<< orphan*/ ,char*,int*) ; 
 char* hci_status2str (int) ; 
 char* hci_ver2str (int) ; 
 int le16toh (int) ; 
 int /*<<< orphan*/  stdout ; 

__attribute__((used)) static int
hci_read_local_version_information(int s, int argc, char **argv)
{
	ng_hci_read_local_ver_rp	rp;
	int				n;

	n = sizeof(rp);
	if (hci_simple_request(s, NG_HCI_OPCODE(NG_HCI_OGF_INFO,
			NG_HCI_OCF_READ_LOCAL_VER), (char *) &rp, &n) == ERROR)
		return (ERROR);

	if (rp.status != 0x00) {
		fprintf(stdout, "Status: %s [%#02x]\n", 
			hci_status2str(rp.status), rp.status);
		return (FAILED);
	}

	rp.manufacturer = le16toh(rp.manufacturer);

	fprintf(stdout, "HCI version: %s [%#02x]\n",
		hci_ver2str(rp.hci_version), rp.hci_version);
	fprintf(stdout, "HCI revision: %#04x\n",
		le16toh(rp.hci_revision));
	fprintf(stdout, "LMP version: %s [%#02x]\n",
		hci_lmpver2str(rp.lmp_version), rp.lmp_version);
	fprintf(stdout, "LMP sub-version: %#04x\n", 
		le16toh(rp.lmp_subversion));
	fprintf(stdout, "Manufacturer: %s [%#04x]\n", 
		hci_manufacturer2str(rp.manufacturer), rp.manufacturer);

	return (OK);
}