#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
#define  ACT_DUMPAP 145 
#define  ACT_DUMPCACHE 144 
#define  ACT_DUMPCAPS 143 
#define  ACT_DUMPCONFIG 142 
#define  ACT_DUMPRSSIMAP 141 
#define  ACT_DUMPSSID 140 
#define  ACT_DUMPSTATS 139 
#define  ACT_DUMPSTATUS 138 
#define  ACT_ENABLE_TX_KEY 137 
 int ACT_ENABLE_WEP ; 
#define  ACT_SET_AP1 136 
#define  ACT_SET_AP2 135 
#define  ACT_SET_AP3 134 
#define  ACT_SET_AP4 133 
 int ACT_SET_BEACON_PERIOD ; 
 int ACT_SET_DIVERSITY_RX ; 
 int ACT_SET_DIVERSITY_TX ; 
 int ACT_SET_FRAG_THRESH ; 
 int ACT_SET_FREQ ; 
#define  ACT_SET_KEYS 132 
 int ACT_SET_KEY_TYPE ; 
#define  ACT_SET_LEAP_MODE 131 
 int ACT_SET_MAC ; 
 int ACT_SET_MONITOR_MODE ; 
 int ACT_SET_MYNAME ; 
 int ACT_SET_NETJOIN ; 
 int ACT_SET_OPMODE ; 
 int ACT_SET_PWRSAVE ; 
 int ACT_SET_RTS_RETRYLIM ; 
 int ACT_SET_RTS_THRESH ; 
#define  ACT_SET_SSID 130 
 int ACT_SET_TXPWR ; 
#define  ACT_SET_TXRATE 129 
 int ACT_SET_WAKE_DURATION ; 
#define  ACT_ZEROCACHE 128 
 int /*<<< orphan*/  an_dumpap (char const*) ; 
 int /*<<< orphan*/  an_dumpcaps (char const*) ; 
 int /*<<< orphan*/  an_dumpconfig (char const*) ; 
 int /*<<< orphan*/  an_dumprssimap (char const*) ; 
 int /*<<< orphan*/  an_dumpssid (char const*) ; 
 int /*<<< orphan*/  an_dumpstats (char const*) ; 
 int /*<<< orphan*/  an_dumpstatus (char const*) ; 
 int /*<<< orphan*/  an_enable_leap_mode (char const*,void*) ; 
 int /*<<< orphan*/  an_enable_tx_key (char const*,void*) ; 
 int /*<<< orphan*/  an_readcache (char const*) ; 
 int /*<<< orphan*/  an_setap (char const*,int,void*) ; 
 int /*<<< orphan*/  an_setconfig (char const*,int,void*) ; 
 int /*<<< orphan*/  an_setkeys (char const*,char*,int) ; 
 int /*<<< orphan*/  an_setspeed (char const*,int,void*) ; 
 int /*<<< orphan*/  an_setssid (char const*,int,void*) ; 
 int /*<<< orphan*/  an_zerocache (char const*) ; 
 int atoi (char*) ; 
 int /*<<< orphan*/  errx (int,char*,...) ; 
 int /*<<< orphan*/  exit (int) ; 
 int getopt (int,char**,char*) ; 
 int /*<<< orphan*/  isdigit (char) ; 
 char* optarg ; 
 int opterr ; 
 int optind ; 
 int optreset ; 
 int /*<<< orphan*/  usage (char*) ; 

int
main(int argc, char *argv[])
{
	int			ch;
	int			act = 0;
	const char		*iface = NULL;
	int			modifier = 0;
	char			*key = NULL;
	void			*arg = NULL;
	char			*p = argv[0];

	/* Get the interface name */
	opterr = 0;
	ch = getopt(argc, argv, "i:");
	if (ch == 'i') {
		iface = optarg;
	} else {
		if (argc > 1 && *argv[1] != '-') {
			iface = argv[1];
			optind = 2; 
		} else {
			iface = "an0";
			optind = 1;
		}
		optreset = 1;
	}
	opterr = 1;

	while ((ch = getopt(argc, argv,
	    "ANISCTRht:a:e:o:s:n:v:d:j:b:c:f:r:p:w:m:l:k:K:W:QZM:L:")) != -1) {
		switch(ch) {
		case 'Z':
#ifdef ANCACHE
			act = ACT_ZEROCACHE;
#else
			errx(1, "ANCACHE not available");
#endif
			break;
		case 'Q':
#ifdef ANCACHE
			act = ACT_DUMPCACHE;
#else
			errx(1, "ANCACHE not available");
#endif
			break;
		case 'A':
			act = ACT_DUMPAP;
			break;
		case 'N':
			act = ACT_DUMPSSID;
			break;
		case 'S':
			act = ACT_DUMPSTATUS;
			break;
		case 'I':
			act = ACT_DUMPCAPS;
			break;
		case 'T':
			act = ACT_DUMPSTATS;
			break;
		case 'C':
			act = ACT_DUMPCONFIG;
			break;
		case 'R':
			act = ACT_DUMPRSSIMAP;
			break;
		case 't':
			act = ACT_SET_TXRATE;
			arg = optarg;
			break;
		case 's':
			act = ACT_SET_PWRSAVE;
			arg = optarg;
			break;
		case 'p':
			act = ACT_SET_TXPWR;
			arg = optarg;
			break;
		case 'v':
			modifier = atoi(optarg);
			break;
		case 'a':
			switch(modifier) {
			case 0:
			case 1:
				act = ACT_SET_AP1;
				break;
			case 2:
				act = ACT_SET_AP2;
				break;
			case 3:
				act = ACT_SET_AP3;
				break;
			case 4:
				act = ACT_SET_AP4;
				break;
			default:
				errx(1, "bad modifier %d: there "
				    "are only 4 access point settings",
				    modifier);
				usage(p);
				break;
			}
			arg = optarg;
			break;
		case 'b':
			act = ACT_SET_BEACON_PERIOD;
			arg = optarg;
			break;
		case 'd':
			switch(modifier) {
			case 0:
				act = ACT_SET_DIVERSITY_RX;
				break;
			case 1:
				act = ACT_SET_DIVERSITY_TX;
				break;
			default:
				errx(1, "must specify RX or TX diversity");
				break;
			}
			if (!isdigit(*optarg)) {
				errx(1, "%s is not numeric", optarg);
				exit(1);
			}
			arg = optarg;
			break;
		case 'j':
			act = ACT_SET_NETJOIN;
			arg = optarg;
			break;
		case 'l':
			act = ACT_SET_MYNAME;
			arg = optarg;
			break;
		case 'm':
			act = ACT_SET_MAC;
			arg = optarg;
			break;
		case 'n':
			if (modifier == 0)
				modifier = 1;
			act = ACT_SET_SSID;
			arg = optarg;
			break;
		case 'o':
			act = ACT_SET_OPMODE;
			arg = optarg;
			break;
		case 'c':
			act = ACT_SET_FREQ;
			arg = optarg;
			break;
		case 'f':
			act = ACT_SET_FRAG_THRESH;
			arg = optarg;
			break;
		case 'W':
			act = ACT_ENABLE_WEP;
			arg = optarg;
			break;
		case 'K':
			act = ACT_SET_KEY_TYPE;
			arg = optarg;
			break;
		case 'k':
			act = ACT_SET_KEYS;
			key = optarg;
			break;
		case 'e':
			act = ACT_ENABLE_TX_KEY;
			arg = optarg;
			break;
		case 'q':
			act = ACT_SET_RTS_RETRYLIM;
			arg = optarg;
			break;
		case 'r':
			act = ACT_SET_RTS_THRESH;
			arg = optarg;
			break;
		case 'w':
			act = ACT_SET_WAKE_DURATION;
			arg = optarg;
			break;
		case 'M':
			act = ACT_SET_MONITOR_MODE;
			arg = optarg;
			break;
		case 'L':
			act = ACT_SET_LEAP_MODE;
			arg = optarg;
			break;
		case 'h':
		default:
			usage(p);
		}
	}

	if (iface == NULL || (!act && !key))
		usage(p);

	switch(act) {
	case ACT_DUMPSTATUS:
		an_dumpstatus(iface);
		break;
	case ACT_DUMPCAPS:
		an_dumpcaps(iface);
		break;
	case ACT_DUMPSTATS:
		an_dumpstats(iface);
		break;
	case ACT_DUMPCONFIG:
		an_dumpconfig(iface);
		break;
	case ACT_DUMPSSID:
		an_dumpssid(iface);
		break;
	case ACT_DUMPAP:
		an_dumpap(iface);
		break;
	case ACT_DUMPRSSIMAP:
		an_dumprssimap(iface);
		break;
	case ACT_SET_SSID:
		an_setssid(iface, modifier, arg);
		break;
	case ACT_SET_AP1:
	case ACT_SET_AP2:
	case ACT_SET_AP3:
	case ACT_SET_AP4:
		an_setap(iface, act, arg);
		break;
	case ACT_SET_TXRATE:
		an_setspeed(iface, act, arg);
		break;
#ifdef ANCACHE
	case ACT_ZEROCACHE:
		an_zerocache(iface);
		break;
	case ACT_DUMPCACHE:
		an_readcache(iface);
		break;

#endif
	case ACT_SET_KEYS:
		an_setkeys(iface, key, modifier);
		break;
	case ACT_ENABLE_TX_KEY:
		an_enable_tx_key(iface, arg);
		break;
	case ACT_SET_LEAP_MODE:
		an_enable_leap_mode(iface, arg);
		break;
	default:
		an_setconfig(iface, act, arg);
		break;
	}

	exit(0);
}