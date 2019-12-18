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
struct socks {int /*<<< orphan*/  sk_addrlen; int /*<<< orphan*/  sk_addr; int /*<<< orphan*/  sk_sock; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int asprintf (char**,char*,int,char const*,char const*,char const*,char const*) ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  send_to_all ; 
 int sendto (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sstosa (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  syslog (int,char*,char const*) ; 
 int /*<<< orphan*/  warn (char*) ; 
 int /*<<< orphan*/  warnx (char*,int) ; 

__attribute__((used)) static void
logmessage(int pri, const char *timestamp, const char *hostname,
    const char *tag, struct socks *sk, ssize_t nsock, const char *buf)
{
	char *line;
	int len, i, lsent;

	if (nsock == 0) {
		syslog(pri, "%s", buf);
		return;
	}
	if ((len = asprintf(&line, "<%d>%s %s %s: %s", pri, timestamp,
	    hostname, tag, buf)) == -1)
		errx(1, "asprintf");

	lsent = -1;
	for (i = 0; i < nsock; i++) {
		lsent = sendto(sk[i].sk_sock, line, len, 0,
			       sstosa(&sk[i].sk_addr), sk[i].sk_addrlen);
		if (lsent == len && !send_to_all)
			break;
	}
	if (lsent != len) {
		if (lsent == -1)
			warn("sendto");
		else
			warnx("sendto: short send - %d bytes", lsent);
	}

	free(line);
}