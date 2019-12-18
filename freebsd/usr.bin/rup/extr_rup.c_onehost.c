#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xdrproc_t ;
struct timeval {int tv_sec; scalar_t__ tv_usec; } ;
struct TYPE_2__ {int /*<<< orphan*/  s_addr; } ;
struct sockaddr_in {TYPE_1__ sin_addr; } ;
struct hostent {int /*<<< orphan*/  h_addr; } ;
typedef  int /*<<< orphan*/  statstime ;
typedef  int /*<<< orphan*/  host_stat ;
typedef  int /*<<< orphan*/  CLIENT ;

/* Variables and functions */
 scalar_t__ RPC_SUCCESS ; 
 int /*<<< orphan*/  RSTATPROC_STATS ; 
 int /*<<< orphan*/  RSTATPROG ; 
 int /*<<< orphan*/  RSTATVERS_TIME ; 
 int /*<<< orphan*/  bzero (char*,int) ; 
 scalar_t__ clnt_call (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct timeval) ; 
 int /*<<< orphan*/ * clnt_create (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  clnt_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clnt_spcreateerror (char*) ; 
 int /*<<< orphan*/  clnt_sperror (int /*<<< orphan*/ *,char*) ; 
 struct hostent* gethostbyname (char*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rstat_reply (int /*<<< orphan*/ *,struct sockaddr_in*) ; 
 int /*<<< orphan*/  warnx (char*,char*,...) ; 
 scalar_t__ xdr_statstime ; 
 scalar_t__ xdr_void ; 

__attribute__((used)) static int
onehost(char *host)
{
	CLIENT *rstat_clnt;
	statstime host_stat;
	struct sockaddr_in addr;
	struct hostent *hp;
	struct timeval tv;

	hp = gethostbyname(host);
	if (hp == NULL) {
		warnx("unknown host \"%s\"", host);
		return(-1);
	}

	rstat_clnt = clnt_create(host, RSTATPROG, RSTATVERS_TIME, "udp");
	if (rstat_clnt == NULL) {
		warnx("%s %s", host, clnt_spcreateerror(""));
		return(-1);
	}

	bzero((char *)&host_stat, sizeof(host_stat));
	tv.tv_sec = 15;	/* XXX ??? */
	tv.tv_usec = 0;
	if (clnt_call(rstat_clnt, RSTATPROC_STATS,
	    (xdrproc_t)xdr_void, NULL,
	    (xdrproc_t)xdr_statstime, &host_stat, tv) != RPC_SUCCESS) {
		warnx("%s: %s", host, clnt_sperror(rstat_clnt, host));
		clnt_destroy(rstat_clnt);
		return(-1);
	}

	memcpy(&addr.sin_addr.s_addr, hp->h_addr, sizeof(int));
	rstat_reply(&host_stat, &addr);
	clnt_destroy(rstat_clnt);
	return (0);
}