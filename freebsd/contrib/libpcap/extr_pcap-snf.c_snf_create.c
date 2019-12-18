#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_int ;
struct snf_ifaddrs {int snf_ifa_boardnum; struct snf_ifaddrs* snf_ifa_next; int /*<<< orphan*/  snf_ifa_name; } ;
struct pcap_snf {int snf_boardnum; } ;
struct TYPE_5__ {int tstamp_precision_count; int /*<<< orphan*/  activate_op; int /*<<< orphan*/ * tstamp_precision_list; struct pcap_snf* priv; } ;
typedef  TYPE_1__ pcap_t ;

/* Variables and functions */
 int /*<<< orphan*/  PCAP_ERRBUF_SIZE ; 
 int /*<<< orphan*/  PCAP_TSTAMP_PRECISION_MICRO ; 
 int /*<<< orphan*/  PCAP_TSTAMP_PRECISION_NANO ; 
 int /*<<< orphan*/  SNF_VERSION_API ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/ * malloc (int) ; 
 int /*<<< orphan*/  pcap_close (TYPE_1__*) ; 
 TYPE_1__* pcap_create_common (char*,int) ; 
 int /*<<< orphan*/  pcap_fmt_errmsg_for_errno (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  snf_activate ; 
 int /*<<< orphan*/  snf_freeifaddrs (struct snf_ifaddrs*) ; 
 scalar_t__ snf_getifaddrs (struct snf_ifaddrs**) ; 
 scalar_t__ snf_init (int /*<<< orphan*/ ) ; 
 int sscanf (char const*,char*,int*) ; 
 int strlen (char const*) ; 
 scalar_t__ strncmp (char const*,int /*<<< orphan*/ ,size_t) ; 

pcap_t *
snf_create(const char *device, char *ebuf, int *is_ours)
{
	pcap_t *p;
	int boardnum = -1;
	struct snf_ifaddrs *ifaddrs, *ifa;
	size_t devlen;
	struct pcap_snf *ps;

	if (snf_init(SNF_VERSION_API)) {
		/* Can't initialize the API, so no SNF devices */
		*is_ours = 0;
		return NULL;
	}

	/*
	 * Match a given interface name to our list of interface names, from
	 * which we can obtain the intended board number
	 */
	if (snf_getifaddrs(&ifaddrs) || ifaddrs == NULL) {
		/* Can't get SNF addresses */
		*is_ours = 0;
		return NULL;
	}
	devlen = strlen(device) + 1;
	ifa = ifaddrs;
	while (ifa) {
		if (strncmp(device, ifa->snf_ifa_name, devlen) == 0) {
			boardnum = ifa->snf_ifa_boardnum;
			break;
		}
		ifa = ifa->snf_ifa_next;
	}
	snf_freeifaddrs(ifaddrs);

	if (ifa == NULL) {
		/*
		 * If we can't find the device by name, support the name "snfX"
		 * and "snf10gX" where X is the board number.
		 */
		if (sscanf(device, "snf10g%d", &boardnum) != 1 &&
		    sscanf(device, "snf%d", &boardnum) != 1) {
			/* Nope, not a supported name */
			*is_ours = 0;
			return NULL;
		}
	}

	/* OK, it's probably ours. */
	*is_ours = 1;

	p = pcap_create_common(ebuf, sizeof (struct pcap_snf));
	if (p == NULL)
		return NULL;
	ps = p->priv;

	/*
	 * We support microsecond and nanosecond time stamps.
	 */
	p->tstamp_precision_count = 2;
	p->tstamp_precision_list = malloc(2 * sizeof(u_int));
	if (p->tstamp_precision_list == NULL) {
		pcap_fmt_errmsg_for_errno(ebuf, PCAP_ERRBUF_SIZE, errno,
		    "malloc");
		pcap_close(p);
		return NULL;
	}
	p->tstamp_precision_list[0] = PCAP_TSTAMP_PRECISION_MICRO;
	p->tstamp_precision_list[1] = PCAP_TSTAMP_PRECISION_NANO;

	p->activate_op = snf_activate;
	ps->snf_boardnum = boardnum;
	return p;
}