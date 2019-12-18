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
struct printer {int remote; char* remote_host; int /*<<< orphan*/  rp_matches_local; } ;
struct addrinfo {int /*<<< orphan*/  ai_addrlen; int /*<<< orphan*/  ai_addr; struct addrinfo* ai_next; void* ai_flags; void* ai_socktype; void* ai_family; } ;
typedef  int /*<<< orphan*/  lclhost ;
typedef  int /*<<< orphan*/  hints ;
typedef  int /*<<< orphan*/  h2 ;
typedef  int /*<<< orphan*/  h1 ;

/* Variables and functions */
 void* AI_PASSIVE ; 
 int MAXHOSTNAMELEN ; 
 int NI_MAXHOST ; 
 int /*<<< orphan*/  NI_NUMERICHOST ; 
 void* SOCK_STREAM ; 
 int /*<<< orphan*/  asprintf (char**,char*,char*,int /*<<< orphan*/ ) ; 
 void* family ; 
 int /*<<< orphan*/  freeaddrinfo (struct addrinfo*) ; 
 int /*<<< orphan*/  gai_strerror (int) ; 
 int getaddrinfo (char*,int /*<<< orphan*/ *,struct addrinfo*,struct addrinfo**) ; 
 int /*<<< orphan*/  gethostname (char*,int) ; 
 scalar_t__ getnameinfo (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct addrinfo*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ strcmp (char*,char*) ; 

char *
checkremote(struct printer *pp)
{
	char lclhost[MAXHOSTNAMELEN];
	struct addrinfo hints, *local_res, *remote_res, *lr, *rr;
	char *error;
	int ncommonaddrs, errno;
	char h1[NI_MAXHOST], h2[NI_MAXHOST];

	if (!pp->rp_matches_local) { /* Remote printer doesn't match local */
		pp->remote = 1;
		return NULL;
	}

	pp->remote = 0;	/* assume printer is local */
	if (pp->remote_host == NULL)
		return NULL;

	/* get the addresses of the local host */
	gethostname(lclhost, sizeof(lclhost));
	lclhost[sizeof(lclhost) - 1] = '\0';

	memset(&hints, 0, sizeof(hints));
	hints.ai_family = family;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;
	if ((errno = getaddrinfo(lclhost, NULL, &hints, &local_res)) != 0) {
		asprintf(&error, "unable to get official name "
			 "for local machine %s: %s",
			 lclhost, gai_strerror(errno));
		return error;
	}

	/* get the official name of RM */
	memset(&hints, 0, sizeof(hints));
	hints.ai_family = family;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;
	if ((errno = getaddrinfo(pp->remote_host, NULL,
				 &hints, &remote_res)) != 0) {
		asprintf(&error, "unable to get address list for "
			 "remote machine %s: %s",
			 pp->remote_host, gai_strerror(errno));
		freeaddrinfo(local_res);
		return error;
	}

	ncommonaddrs = 0;
	for (lr = local_res; lr; lr = lr->ai_next) {
		h1[0] = '\0';
		if (getnameinfo(lr->ai_addr, lr->ai_addrlen, h1, sizeof(h1),
				NULL, 0, NI_NUMERICHOST) != 0)
			continue;
		for (rr = remote_res; rr; rr = rr->ai_next) {
			h2[0] = '\0';
			if (getnameinfo(rr->ai_addr, rr->ai_addrlen,
					h2, sizeof(h2), NULL, 0,
					NI_NUMERICHOST) != 0)
				continue;
			if (strcmp(h1, h2) == 0)
				ncommonaddrs++;
		}
	}
			
	/*
	 * if the two hosts do not share at least one IP address
	 * then the printer must be remote.
	 */
	if (ncommonaddrs == 0)
		pp->remote = 1;
	freeaddrinfo(local_res);
	freeaddrinfo(remote_res);
	return NULL;
}