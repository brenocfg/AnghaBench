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
struct addrinfo {struct addrinfo* ai_next; scalar_t__ ai_addr; int /*<<< orphan*/  ai_socktype; int /*<<< orphan*/  ai_family; } ;
struct activehosts {struct activehosts* next; int /*<<< orphan*/  host; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCAP_ERRBUF_SIZE ; 
 int /*<<< orphan*/  PF_UNSPEC ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 struct activehosts* activeHosts ; 
 int /*<<< orphan*/  freeaddrinfo (struct addrinfo*) ; 
 int /*<<< orphan*/  gai_strerror (int) ; 
 int getaddrinfo (char const*,char*,struct addrinfo*,struct addrinfo**) ; 
 int /*<<< orphan*/  memset (struct addrinfo*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pcap_snprintf (char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ sock_cmpaddr (int /*<<< orphan*/ *,struct sockaddr_storage*) ; 

__attribute__((used)) static struct activehosts *
rpcap_remoteact_getsock(const char *host, int *error, char *errbuf)
{
	struct activehosts *temp;			/* temp var needed to scan the host list chain */
	struct addrinfo hints, *addrinfo, *ai_next;	/* temp var needed to translate between hostname to its address */
	int retval;

	/* retrieve the network address corresponding to 'host' */
	addrinfo = NULL;
	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_family = PF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;

	retval = getaddrinfo(host, "0", &hints, &addrinfo);
	if (retval != 0)
	{
		pcap_snprintf(errbuf, PCAP_ERRBUF_SIZE, "getaddrinfo() %s",
		    gai_strerror(retval));
		*error = 1;
		return NULL;
	}

	temp = activeHosts;

	while (temp)
	{
		ai_next = addrinfo;
		while (ai_next)
		{
			if (sock_cmpaddr(&temp->host, (struct sockaddr_storage *) ai_next->ai_addr) == 0)
			{
				*error = 0;
				freeaddrinfo(addrinfo);
				return temp;
			}

			ai_next = ai_next->ai_next;
		}
		temp = temp->next;
	}

	if (addrinfo)
		freeaddrinfo(addrinfo);

	/*
	 * The host for which you want to get the socket ID does not have an
	 * active connection.
	 */
	*error = 0;
	return NULL;
}