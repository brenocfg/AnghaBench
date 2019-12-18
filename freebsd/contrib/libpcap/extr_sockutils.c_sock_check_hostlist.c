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

/* Variables and functions */
 int /*<<< orphan*/  PF_UNSPEC ; 
 int /*<<< orphan*/  SOCK_DEBUG_MESSAGE (char*) ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  freeaddrinfo (struct addrinfo*) ; 
 int /*<<< orphan*/  gai_strerror (int) ; 
 int getaddrinfo (char*,char*,struct addrinfo*,struct addrinfo**) ; 
 int /*<<< orphan*/  memset (struct addrinfo*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pcap_snprintf (char*,int,char*,...) ; 
 char* pcap_strtok_r (char*,char const*,char**) ; 
 scalar_t__ sock_cmpaddr (struct sockaddr_storage*,struct sockaddr_storage*) ; 
 int /*<<< orphan*/  sock_geterror (char*,char*,int) ; 
 char* strdup (char*) ; 

int sock_check_hostlist(char *hostlist, const char *sep, struct sockaddr_storage *from, char *errbuf, int errbuflen)
{
	/* checks if the connecting host is among the ones allowed */
	if ((hostlist) && (hostlist[0]))
	{
		char *token;					/* temp, needed to separate items into the hostlist */
		struct addrinfo *addrinfo, *ai_next;
		char *temphostlist;
		char *lasts;

		/*
		 * The problem is that strtok modifies the original variable by putting '0' at the end of each token
		 * So, we have to create a new temporary string in which the original content is kept
		 */
		temphostlist = strdup(hostlist);
		if (temphostlist == NULL)
		{
			sock_geterror("sock_check_hostlist(), malloc() failed", errbuf, errbuflen);
			return -2;
		}

		token = pcap_strtok_r(temphostlist, sep, &lasts);

		/* it avoids a warning in the compilation ('addrinfo used but not initialized') */
		addrinfo = NULL;

		while (token != NULL)
		{
			struct addrinfo hints;
			int retval;

			addrinfo = NULL;
			memset(&hints, 0, sizeof(struct addrinfo));
			hints.ai_family = PF_UNSPEC;
			hints.ai_socktype = SOCK_STREAM;

			retval = getaddrinfo(token, "0", &hints, &addrinfo);
			if (retval != 0)
			{
				if (errbuf)
					pcap_snprintf(errbuf, errbuflen, "getaddrinfo() %s", gai_strerror(retval));

				SOCK_DEBUG_MESSAGE(errbuf);

				/* Get next token */
				token = pcap_strtok_r(NULL, sep, &lasts);
				continue;
			}

			/* ai_next is required to preserve the content of addrinfo, in order to deallocate it properly */
			ai_next = addrinfo;
			while (ai_next)
			{
				if (sock_cmpaddr(from, (struct sockaddr_storage *) ai_next->ai_addr) == 0)
				{
					free(temphostlist);
					freeaddrinfo(addrinfo);
					return 0;
				}

				/*
				 * If we are here, it means that the current address does not matches
				 * Let's try with the next one in the header chain
				 */
				ai_next = ai_next->ai_next;
			}

			freeaddrinfo(addrinfo);
			addrinfo = NULL;

			/* Get next token */
			token = pcap_strtok_r(NULL, sep, &lasts);
		}

		if (addrinfo)
		{
			freeaddrinfo(addrinfo);
			addrinfo = NULL;
		}

		if (errbuf)
			pcap_snprintf(errbuf, errbuflen, "The host is not in the allowed host list. Connection refused.");

		free(temphostlist);
		return -1;
	}

	/* No hostlist, so we have to return 'empty list' */
	return 1;
}