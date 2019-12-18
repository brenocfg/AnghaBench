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
typedef  int /*<<< orphan*/  kvm_t ;
struct TYPE_2__ {int /*<<< orphan*/  n_value; } ;

/* Variables and functions */
#define  N_HCI_RAW 132 
#define  N_L2CAP 131 
#define  N_L2CAP_RAW 130 
 size_t N_L2CAP_RAW_RT ; 
 size_t N_L2CAP_RT ; 
#define  N_RFCOMM 129 
#define  N_RFCOMM_S 128 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  getgid () ; 
 int getopt (int,char**,char*) ; 
 int /*<<< orphan*/  hcirawpr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * kopen (char*) ; 
 int kvm_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  l2cappr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  l2caprawpr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  l2caprtpr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__* nl ; 
 int numeric_bdaddr ; 
 char* optarg ; 
 int /*<<< orphan*/  rfcommpr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rfcommpr_s (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ setgid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcasecmp (char*,char*) ; 
 int /*<<< orphan*/  usage () ; 

int
main(int argc, char *argv[])
{
	int	 opt, proto = -1, route = 0;
	kvm_t	*kvmd = NULL;
	char	*memf = NULL;

	while ((opt = getopt(argc, argv, "hnM:p:r")) != -1) {
		switch (opt) {
		case 'n':
			numeric_bdaddr = 1;
			break;

		case 'M':
			memf = optarg;
			break;

		case 'p':
			if (strcasecmp(optarg, "hci_raw") == 0)
				proto = N_HCI_RAW;
			else if (strcasecmp(optarg, "l2cap_raw") == 0)
				proto = N_L2CAP_RAW;
			else if (strcasecmp(optarg, "l2cap") == 0)
				proto = N_L2CAP;
			else if (strcasecmp(optarg, "rfcomm") == 0)
				proto = N_RFCOMM;
			else if (strcasecmp(optarg, "rfcomm_s") == 0)
				proto = N_RFCOMM_S; 
			else
				usage();
				/* NOT REACHED */
			break;

		case 'r':
			route = 1;
			break;

		case 'h':
		default:
			usage();
			/* NOT REACHED */
		}
	}

	if ((proto == N_HCI_RAW || proto == N_RFCOMM || proto == N_RFCOMM_S) && route)
		usage();
		/* NOT REACHED */

	/*
	 * Discard setgid privileges if not the running kernel so that
	 * bad guys can't print interesting stuff from kernel memory.
	 */
	if (memf != NULL)
		if (setgid(getgid()) != 0)
			err(1, "setgid");

	kvmd = kopen(memf);
	if (kvmd == NULL)
		return (1);

	switch (proto) {
	case N_HCI_RAW:
		hcirawpr(kvmd, nl[N_HCI_RAW].n_value);
		break;

	case N_L2CAP_RAW:
		if (route)
			l2caprtpr(kvmd, nl[N_L2CAP_RAW_RT].n_value);
		else
			l2caprawpr(kvmd, nl[N_L2CAP_RAW].n_value);
		break;

	case N_L2CAP:
		if (route) 
			l2caprtpr(kvmd, nl[N_L2CAP_RT].n_value);
		else
			l2cappr(kvmd, nl[N_L2CAP].n_value);
		break;

	case N_RFCOMM:
		rfcommpr(kvmd, nl[N_RFCOMM].n_value);
		break;

	case N_RFCOMM_S:
		rfcommpr_s(kvmd, nl[N_RFCOMM_S].n_value);
		break;

	default:
		if (route) {
			l2caprtpr(kvmd, nl[N_L2CAP_RAW_RT].n_value);
			l2caprtpr(kvmd, nl[N_L2CAP_RT].n_value);
		} else {
			hcirawpr(kvmd, nl[N_HCI_RAW].n_value);
			l2caprawpr(kvmd, nl[N_L2CAP_RAW].n_value);
			l2cappr(kvmd, nl[N_L2CAP].n_value);
			rfcommpr_s(kvmd, nl[N_RFCOMM_S].n_value);
			rfcommpr(kvmd, nl[N_RFCOMM].n_value);
		}
		break;
	}

	return (kvm_close(kvmd));
}