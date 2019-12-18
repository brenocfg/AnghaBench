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
struct addrinfo {scalar_t__ ai_family; int /*<<< orphan*/  ai_addrlen; int /*<<< orphan*/  ai_addr; struct addrinfo* ai_next; } ;
typedef  int /*<<< orphan*/  conn_t ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGF (char*,char const*,int) ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int bind (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close (int) ; 
 int connect (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fetch_info (char*,char const*,...) ; 
 int /*<<< orphan*/ * fetch_reopen (int) ; 
 struct addrinfo* fetch_resolve (char const*,int,int) ; 
 int /*<<< orphan*/  fetch_syserr () ; 
 int /*<<< orphan*/  freeaddrinfo (struct addrinfo*) ; 
 char* getenv (char*) ; 
 int socket (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

conn_t *
fetch_connect(const char *host, int port, int af, int verbose)
{
	struct addrinfo *cais = NULL, *sais = NULL, *cai, *sai;
	const char *bindaddr;
	conn_t *conn = NULL;
	int err = 0, sd = -1;

	DEBUGF("---> %s:%d\n", host, port);

	/* resolve server address */
	if (verbose)
		fetch_info("resolving server address: %s:%d", host, port);
	if ((sais = fetch_resolve(host, port, af)) == NULL)
		goto fail;

	/* resolve client address */
	bindaddr = getenv("FETCH_BIND_ADDRESS");
	if (bindaddr != NULL && *bindaddr != '\0') {
		if (verbose)
			fetch_info("resolving client address: %s", bindaddr);
		if ((cais = fetch_resolve(bindaddr, 0, af)) == NULL)
			goto fail;
	}

	/* try each server address in turn */
	for (err = 0, sai = sais; sai != NULL; sai = sai->ai_next) {
		/* open socket */
		if ((sd = socket(sai->ai_family, SOCK_STREAM, 0)) < 0)
			goto syserr;
		/* attempt to bind to client address */
		for (err = 0, cai = cais; cai != NULL; cai = cai->ai_next) {
			if (cai->ai_family != sai->ai_family)
				continue;
			if ((err = bind(sd, cai->ai_addr, cai->ai_addrlen)) == 0)
				break;
		}
		if (err != 0) {
			if (verbose)
				fetch_info("failed to bind to %s", bindaddr);
			goto syserr;
		}
		/* attempt to connect to server address */
		if ((err = connect(sd, sai->ai_addr, sai->ai_addrlen)) == 0)
			break;
		/* clean up before next attempt */
		close(sd);
		sd = -1;
	}
	if (err != 0) {
		if (verbose)
			fetch_info("failed to connect to %s:%d", host, port);
		goto syserr;
	}

	if ((conn = fetch_reopen(sd)) == NULL)
		goto syserr;
	if (cais != NULL)
		freeaddrinfo(cais);
	if (sais != NULL)
		freeaddrinfo(sais);
	return (conn);
syserr:
	fetch_syserr();
	goto fail;
fail:
	if (sd >= 0)
		close(sd);
	if (cais != NULL)
		freeaddrinfo(cais);
	if (sais != NULL)
		freeaddrinfo(sais);
	return (NULL);
}