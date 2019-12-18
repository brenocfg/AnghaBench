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
typedef  int /*<<< orphan*/  ng_hci_le_set_scan_parameters_rp ;
struct TYPE_2__ {int le_scan_type; int le_scan_interval; int own_address_type; int le_scan_window; int scanning_filter_policy; } ;
typedef  TYPE_1__ ng_hci_le_set_scan_parameters_cp ;
typedef  int /*<<< orphan*/  cp ;

/* Variables and functions */
 int /*<<< orphan*/  NG_HCI_OCF_LE_SET_SCAN_PARAMETERS ; 
 int /*<<< orphan*/  NG_HCI_OGF_LE ; 
 int /*<<< orphan*/  NG_HCI_OPCODE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int USAGE ; 
 double atof (char*) ; 
 int hci_request (int,int /*<<< orphan*/ ,void*,int,void*,int*) ; 
 scalar_t__ strcmp (char*,char*) ; 

__attribute__((used)) static int
le_set_scan_param(int s, int argc, char *argv[])
{
	int type;
	int interval;
	int window;
	int adrtype;
	int policy;
	int e, n;

	ng_hci_le_set_scan_parameters_cp cp;
	ng_hci_le_set_scan_parameters_rp rp;

	if (argc != 5)
		return USAGE;
	
	if (strcmp(argv[0], "active") == 0)
		type = 1;
	else if (strcmp(argv[0], "passive") == 0)
		type = 0;
	else
		return USAGE;

	interval = (int)(atof(argv[1])/0.625);
	interval = (interval < 4)? 4: interval;
	window = (int)(atof(argv[2])/0.625);
	window = (window < 4) ? 4 : interval;
	
	if (strcmp(argv[3], "public") == 0)
		adrtype = 0;
	else if (strcmp(argv[3], "random") == 0)
		adrtype = 1;
	else
		return USAGE;

	if (strcmp(argv[4], "all") == 0)
		policy = 0;
	else if (strcmp(argv[4], "whitelist") == 0)
		policy = 1;
	else
		return USAGE;

	cp.le_scan_type = type;
	cp.le_scan_interval = interval;
	cp.own_address_type = adrtype;
	cp.le_scan_window = window;
	cp.scanning_filter_policy = policy;
	n = sizeof(rp);
	e = hci_request(s, NG_HCI_OPCODE(NG_HCI_OGF_LE,
		NG_HCI_OCF_LE_SET_SCAN_PARAMETERS), 
		(void *)&cp, sizeof(cp), (void *)&rp, &n);

	return 0;
}