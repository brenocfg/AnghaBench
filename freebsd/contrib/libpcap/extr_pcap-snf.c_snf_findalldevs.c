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
struct sockaddr_in {int /*<<< orphan*/  sin_family; int /*<<< orphan*/  sin_addr; } ;
struct snf_ifaddrs {int snf_ifa_portnum; char* snf_ifa_name; struct snf_ifaddrs* snf_ifa_next; } ;
struct TYPE_5__ {char* description; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ pcap_if_t ;
typedef  int /*<<< orphan*/  pcap_if_list_t ;
typedef  int /*<<< orphan*/  addr ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int MAX_DESC_LENGTH ; 
 int /*<<< orphan*/  PCAP_ERRBUF_SIZE ; 
 int /*<<< orphan*/  PCAP_IF_CONNECTION_STATUS_NOT_APPLICABLE ; 
 int SNF_F_AGGREGATE_PORTMASK ; 
 int /*<<< orphan*/  SNF_VERSION_API ; 
 int add_addr_to_dev (TYPE_1__*,struct sockaddr_in*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 TYPE_1__* add_dev (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,char*,char*) ; 
 scalar_t__ errno ; 
 TYPE_1__* find_dev (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* getenv (char*) ; 
 int inet_pton (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pcap_fmt_errmsg_for_errno (char*,int /*<<< orphan*/ ,scalar_t__,char*) ; 
 int /*<<< orphan*/  pcap_snprintf (char*,int,char*,...) ; 
 int /*<<< orphan*/  snf_freeifaddrs (struct snf_ifaddrs*) ; 
 scalar_t__ snf_getifaddrs (struct snf_ifaddrs**) ; 
 scalar_t__ snf_init (int /*<<< orphan*/ ) ; 
 char* strdup (char*) ; 
 int strtol (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int
snf_findalldevs(pcap_if_list_t *devlistp, char *errbuf)
{
	pcap_if_t *dev;
#ifdef _WIN32
	struct sockaddr_in addr;
#endif
	struct snf_ifaddrs *ifaddrs, *ifa;
	char name[MAX_DESC_LENGTH];
	char desc[MAX_DESC_LENGTH];
	int ret, allports = 0, merge = 0;
	const char *nr = NULL;

	if (snf_init(SNF_VERSION_API)) {
		(void)pcap_snprintf(errbuf, PCAP_ERRBUF_SIZE,
		    "snf_getifaddrs: snf_init failed");
		return (-1);
	}

	if (snf_getifaddrs(&ifaddrs) || ifaddrs == NULL)
	{
		pcap_fmt_errmsg_for_errno(errbuf, PCAP_ERRBUF_SIZE,
		    errno, "snf_getifaddrs");
		return (-1);
	}
	if ((nr = getenv("SNF_FLAGS")) && *nr) {
		errno = 0;
		merge = strtol(nr, NULL, 0);
		if (errno) {
			(void)pcap_snprintf(errbuf, PCAP_ERRBUF_SIZE,
				"snf_getifaddrs: SNF_FLAGS is not a valid number");
			return (-1);
		}
		merge = merge & SNF_F_AGGREGATE_PORTMASK;
	}

	for (ifa = ifaddrs; ifa != NULL; ifa = ifa->snf_ifa_next) {
		/*
		 * Myricom SNF adapter ports may appear as regular
		 * network interfaces, which would already have been
		 * added to the list of adapters by pcap_platform_finddevs()
		 * if this isn't an SNF-only version of libpcap.
		 *
		 * Our create routine intercepts pcap_create() calls for
		 * those interfaces and arranges that they will be
		 * opened using the SNF API instead.
		 *
		 * So if we already have an entry for the device, we
		 * don't add an additional entry for it, we just
		 * update the description for it, if any, to indicate
		 * which snfN device it is.  Otherwise, we add an entry
		 * for it.
		 *
		 * In either case, if SNF_F_AGGREGATE_PORTMASK is set
		 * in SNF_FLAGS, we add this port to the bitmask
		 * of ports, which we use to generate a device
		 * we can use to capture on all ports.
		 *
		 * Generate the description string.  If port aggregation
		 * is set, use 2^{port number} as the unit number,
		 * rather than {port number}.
		 *
		 * XXX - do entries in this list have IP addresses for
		 * the port?  If so, should we add them to the
		 * entry for the device, if they're not already in the
		 * list of IP addresses for the device?
 		 */
		(void)pcap_snprintf(desc,MAX_DESC_LENGTH,"Myricom %ssnf%d",
			merge ? "Merge Bitmask Port " : "",
			merge ? 1 << ifa->snf_ifa_portnum : ifa->snf_ifa_portnum);
		/*
		 * Add the port to the bitmask.
		 */
		if (merge)
			allports |= 1 << ifa->snf_ifa_portnum;
		/*
		 * See if there's already an entry for the device
		 * with the name ifa->snf_ifa_name.
		 */
		dev = find_dev(devlistp, ifa->snf_ifa_name);
		if (dev != NULL) {
			/*
			 * Yes.  Update its description.
			 */
			char *desc_str;

			desc_str = strdup(desc);
			if (desc_str == NULL) {
				pcap_fmt_errmsg_for_errno(errbuf,
				    PCAP_ERRBUF_SIZE, errno,
				    "snf_findalldevs strdup");
				return -1;
			}
			free(dev->description);
			dev->description = desc_str;
		} else {
			/*
			 * No.  Add an entry for it.
			 *
			 * XXX - is there a notion of "up" or "running",
			 * and can we determine whether something's
			 * plugged into the adapter and set
			 * PCAP_IF_CONNECTION_STATUS_CONNECTED or
			 * PCAP_IF_CONNECTION_STATUS_DISCONNECTED?
			 */
			dev = add_dev(devlistp, ifa->snf_ifa_name, 0, desc,
			    errbuf);
			if (dev == NULL)
				return -1;
#ifdef _WIN32
			/*
			 * On Windows, fill in IP# from device name
			 */
                        ret = inet_pton(AF_INET, dev->name, &addr.sin_addr);
                        if (ret == 1) {
                        	/*
                        	 * Successful conversion of device name
                        	 * to IPv4 address.
                        	 */
	                        addr.sin_family = AF_INET;
        	                if (add_addr_to_dev(dev, &addr, sizeof(addr),
                	            NULL, 0, NULL, 0, NULL, 0, errbuf) == -1)
                        		return -1;
                        } else if (ret == -1) {
				/*
				 * Error.
				 */
				pcap_fmt_errmsg_for_errno(errbuf,
				    PCAP_ERRBUF_SIZE, errno,
				    "sinf_findalldevs inet_pton");
                                return -1;
                        }
#endif _WIN32
		}
	}
	snf_freeifaddrs(ifaddrs);
	/*
	 * Create a snfX entry if port aggregation is enabled
       	 */
	if (merge) {
		/*
		 * Add a new entry with all ports bitmask
		 */
		(void)pcap_snprintf(name,MAX_DESC_LENGTH,"snf%d",allports);
		(void)pcap_snprintf(desc,MAX_DESC_LENGTH,"Myricom Merge Bitmask All Ports snf%d",
			allports);
		/*
		 * XXX - is there any notion of "up" and "running" that
		 * would apply to this device, given that it handles
		 * multiple ports?
		 *
		 * Presumably, there's no notion of "connected" vs.
		 * "disconnected", as "is this plugged into a network?"
		 * would be a per-port property.
		 */
		if (add_dev(devlistp, name,
		    PCAP_IF_CONNECTION_STATUS_NOT_APPLICABLE, desc,
		    errbuf) == NULL)
			return (-1);
		/*
		 * XXX - should we give it a list of addresses with all
		 * the addresses for all the ports?
		 */
	}

	return 0;
}