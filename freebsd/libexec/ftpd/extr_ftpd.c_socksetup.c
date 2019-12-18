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
struct addrinfo {int ai_family; int /*<<< orphan*/  ai_addrlen; int /*<<< orphan*/  ai_addr; int /*<<< orphan*/  ai_protocol; int /*<<< orphan*/  ai_socktype; struct addrinfo* ai_next; int /*<<< orphan*/  ai_flags; } ;
typedef  int /*<<< orphan*/  on ;
typedef  int /*<<< orphan*/  hints ;

/* Variables and functions */
 scalar_t__ AF_INET6 ; 
 int /*<<< orphan*/  AI_PASSIVE ; 
 int EAI_SYSTEM ; 
 int /*<<< orphan*/  IPPROTO_IPV6 ; 
 int /*<<< orphan*/  IPV6_V6ONLY ; 
 int /*<<< orphan*/  LOG_DEBUG ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  LOG_WARNING ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SO_REUSEADDR ; 
 scalar_t__ bind (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  free (int*) ; 
 int /*<<< orphan*/  freeaddrinfo (struct addrinfo*) ; 
 int /*<<< orphan*/  gai_strerror (int) ; 
 int getaddrinfo (char*,char const*,struct addrinfo*,struct addrinfo**) ; 
 int* malloc (int) ; 
 int /*<<< orphan*/  memset (struct addrinfo*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ setsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int const*,int) ; 
 int socket (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static int *
socksetup(int af, char *bindname, const char *bindport)
{
	struct addrinfo hints, *res, *r;
	int error, maxs, *s, *socks;
	const int on = 1;

	memset(&hints, 0, sizeof(hints));
	hints.ai_flags = AI_PASSIVE;
	hints.ai_family = af;
	hints.ai_socktype = SOCK_STREAM;
	error = getaddrinfo(bindname, bindport, &hints, &res);
	if (error) {
		syslog(LOG_ERR, "%s", gai_strerror(error));
		if (error == EAI_SYSTEM)
			syslog(LOG_ERR, "%s", strerror(errno));
		return NULL;
	}

	/* Count max number of sockets we may open */
	for (maxs = 0, r = res; r; r = r->ai_next, maxs++)
		;
	socks = malloc((maxs + 1) * sizeof(int));
	if (!socks) {
		freeaddrinfo(res);
		syslog(LOG_ERR, "couldn't allocate memory for sockets");
		return NULL;
	}

	*socks = 0;   /* num of sockets counter at start of array */
	s = socks + 1;
	for (r = res; r; r = r->ai_next) {
		*s = socket(r->ai_family, r->ai_socktype, r->ai_protocol);
		if (*s < 0) {
			syslog(LOG_DEBUG, "control socket: %m");
			continue;
		}
		if (setsockopt(*s, SOL_SOCKET, SO_REUSEADDR,
		    &on, sizeof(on)) < 0)
			syslog(LOG_WARNING,
			    "control setsockopt (SO_REUSEADDR): %m");
		if (r->ai_family == AF_INET6) {
			if (setsockopt(*s, IPPROTO_IPV6, IPV6_V6ONLY,
			    &on, sizeof(on)) < 0)
				syslog(LOG_WARNING,
				    "control setsockopt (IPV6_V6ONLY): %m");
		}
		if (bind(*s, r->ai_addr, r->ai_addrlen) < 0) {
			syslog(LOG_DEBUG, "control bind: %m");
			close(*s);
			continue;
		}
		(*socks)++;
		s++;
	}

	if (res)
		freeaddrinfo(res);

	if (*socks == 0) {
		syslog(LOG_ERR, "control socket: Couldn't bind to any socket");
		free(socks);
		return NULL;
	}
	return(socks);
}