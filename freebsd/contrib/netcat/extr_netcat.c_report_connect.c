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
struct sockaddr {int dummy; } ;
typedef  int /*<<< orphan*/  socklen_t ;
typedef  int /*<<< orphan*/  remote_port ;
typedef  int /*<<< orphan*/  remote_host ;

/* Variables and functions */
 int EAI_SYSTEM ; 
 int NI_MAXHOST ; 
 int NI_MAXSERV ; 
 int NI_NUMERICHOST ; 
 int NI_NUMERICSERV ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  errx (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,char*) ; 
 int /*<<< orphan*/  gai_strerror (int) ; 
 int getnameinfo (struct sockaddr const*,int /*<<< orphan*/ ,char*,int,char*,int,int) ; 
 scalar_t__ nflag ; 
 int /*<<< orphan*/  stderr ; 

void
report_connect(const struct sockaddr *sa, socklen_t salen)
{
	char remote_host[NI_MAXHOST];
	char remote_port[NI_MAXSERV];
	int herr;
	int flags = NI_NUMERICSERV;
	
	if (nflag)
		flags |= NI_NUMERICHOST;
	
	if ((herr = getnameinfo(sa, salen,
	    remote_host, sizeof(remote_host),
	    remote_port, sizeof(remote_port),
	    flags)) != 0) {
		if (herr == EAI_SYSTEM)
			err(1, "getnameinfo");
		else
			errx(1, "getnameinfo: %s", gai_strerror(herr));
	}
	
	fprintf(stderr,
	    "Connection from %s %s "
	    "received!\n", remote_host, remote_port);
}