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
struct sockaddr_in6 {int dummy; } ;
struct sockaddr_in {int dummy; } ;
struct addrinfo {int ai_family; int /*<<< orphan*/ * ai_next; int /*<<< orphan*/  ai_addr; } ;
typedef  int /*<<< orphan*/  hints ;

/* Variables and functions */
 scalar_t__ PF_INET ; 
 int /*<<< orphan*/  freeaddrinfo (struct addrinfo*) ; 
 int /*<<< orphan*/  memcpy (struct sockaddr_storage*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (struct addrinfo*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pcap_snprintf (char*,int,char*) ; 
 int sock_initaddress (char const*,char*,struct addrinfo*,struct addrinfo**,char*,int) ; 

int sock_present2network(const char *address, struct sockaddr_storage *sockaddr, int addr_family, char *errbuf, int errbuflen)
{
	int retval;
	struct addrinfo *addrinfo;
	struct addrinfo hints;

	memset(&hints, 0, sizeof(hints));

	hints.ai_family = addr_family;

	if ((retval = sock_initaddress(address, "22222" /* fake port */, &hints, &addrinfo, errbuf, errbuflen)) == -1)
		return 0;

	if (addrinfo->ai_family == PF_INET)
		memcpy(sockaddr, addrinfo->ai_addr, sizeof(struct sockaddr_in));
	else
		memcpy(sockaddr, addrinfo->ai_addr, sizeof(struct sockaddr_in6));

	if (addrinfo->ai_next != NULL)
	{
		freeaddrinfo(addrinfo);

		if (errbuf)
			pcap_snprintf(errbuf, errbuflen, "More than one socket requested; using the first one returned");
		return -2;
	}

	freeaddrinfo(addrinfo);
	return -1;
}