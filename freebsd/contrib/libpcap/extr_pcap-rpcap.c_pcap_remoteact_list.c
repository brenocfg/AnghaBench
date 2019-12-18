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
struct sockaddr_storage {int dummy; } ;
struct activehosts {struct activehosts* next; int /*<<< orphan*/  host; } ;

/* Variables and functions */
 int /*<<< orphan*/  NI_NUMERICHOST ; 
 int /*<<< orphan*/  PCAP_ERRBUF_SIZE ; 
 int /*<<< orphan*/  RPCAP_HOSTLIST_SIZE ; 
 struct activehosts* activeHosts ; 
 int /*<<< orphan*/  pcap_snprintf (char*,int /*<<< orphan*/ ,char*) ; 
 int sock_getascii_addrport (struct sockaddr_storage*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcat (char*,char*,int /*<<< orphan*/ ) ; 
 size_t strlen (char*) ; 

int pcap_remoteact_list(char *hostlist, char sep, int size, char *errbuf)
{
	struct activehosts *temp;	/* temp var needed to scan the host list chain */
	size_t len;
	char hoststr[RPCAP_HOSTLIST_SIZE + 1];

	temp = activeHosts;

	len = 0;
	*hostlist = 0;

	while (temp)
	{
		/*int sock_getascii_addrport(const struct sockaddr_storage *sockaddr, char *address, int addrlen, char *port, int portlen, int flags, char *errbuf, int errbuflen) */

		/* Get the numeric form of the name of the connecting host */
		if (sock_getascii_addrport((struct sockaddr_storage *) &temp->host, hoststr,
			RPCAP_HOSTLIST_SIZE, NULL, 0, NI_NUMERICHOST, errbuf, PCAP_ERRBUF_SIZE) != -1)
			/*	if (getnameinfo( (struct sockaddr *) &temp->host, sizeof (struct sockaddr_storage), hoststr, */
			/*		RPCAP_HOSTLIST_SIZE, NULL, 0, NI_NUMERICHOST) ) */
		{
			/*	sock_geterror("getnameinfo(): ", errbuf, PCAP_ERRBUF_SIZE); */
			return -1;
		}

		len = len + strlen(hoststr) + 1 /* the separator */;

		if ((size < 0) || (len >= (size_t)size))
		{
			pcap_snprintf(errbuf, PCAP_ERRBUF_SIZE, "The string you provided is not able to keep "
				"the hostnames for all the active connections");
			return -1;
		}

		strlcat(hostlist, hoststr, PCAP_ERRBUF_SIZE);
		hostlist[len - 1] = sep;
		hostlist[len] = 0;

		temp = temp->next;
	}

	return 0;
}