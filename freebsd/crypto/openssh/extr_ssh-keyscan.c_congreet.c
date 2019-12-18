#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {char* c_name; TYPE_2__* c_ssh; } ;
typedef  TYPE_1__ con ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_9__ {scalar_t__ compat; } ;

/* Variables and functions */
#define  ECONNREFUSED 129 
#define  EPIPE 128 
 int PROTOCOL_MAJOR_2 ; 
 int PROTOCOL_MINOR_2 ; 
 size_t atomicio (int /*<<< orphan*/ ,int,char*,int) ; 
 char* chop (char*) ; 
 scalar_t__ compat_datafellows (char*) ; 
 int /*<<< orphan*/  confree (int) ; 
 int /*<<< orphan*/  conrecycle (int) ; 
 int /*<<< orphan*/  debug (char*,char*) ; 
 int errno ; 
 int /*<<< orphan*/  error (char*,...) ; 
 int /*<<< orphan*/  fatal (char*) ; 
 TYPE_1__* fdcon ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char,char*,int,char*) ; 
 int /*<<< orphan*/  keygrab_ssh2 (TYPE_1__*) ; 
 int /*<<< orphan*/  memset (char*,char,int) ; 
 scalar_t__ print_sshfp ; 
 int /*<<< orphan*/  read ; 
 int snprintf (char*,int,char*,int,int) ; 
 int sscanf (char*,char*,int*,int*,char*) ; 
 int /*<<< orphan*/  ssh2_capable (int,int) ; 
 TYPE_2__* ssh_packet_set_connection (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  ssh_packet_set_timeout (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int ssh_port ; 
 int /*<<< orphan*/  ssh_set_app_data (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  stderr ; 
 char* strerror (int) ; 
 scalar_t__ strncmp (char*,char*,int) ; 
 int /*<<< orphan*/  timeout ; 
 int /*<<< orphan*/  vwrite ; 

__attribute__((used)) static void
congreet(int s)
{
	int n = 0, remote_major = 0, remote_minor = 0;
	char buf[256], *cp;
	char remote_version[sizeof buf];
	size_t bufsiz;
	con *c = &fdcon[s];

	/* send client banner */
	n = snprintf(buf, sizeof buf, "SSH-%d.%d-OpenSSH-keyscan\r\n",
	    PROTOCOL_MAJOR_2, PROTOCOL_MINOR_2);
	if (n < 0 || (size_t)n >= sizeof(buf)) {
		error("snprintf: buffer too small");
		confree(s);
		return;
	}
	if (atomicio(vwrite, s, buf, n) != (size_t)n) {
		error("write (%s): %s", c->c_name, strerror(errno));
		confree(s);
		return;
	}

	for (;;) {
		memset(buf, '\0', sizeof(buf));
		bufsiz = sizeof(buf);
		cp = buf;
		while (bufsiz-- &&
		    (n = atomicio(read, s, cp, 1)) == 1 && *cp != '\n') {
			if (*cp == '\r')
				*cp = '\n';
			cp++;
		}
		if (n != 1 || strncmp(buf, "SSH-", 4) == 0)
			break;
	}
	if (n == 0) {
		switch (errno) {
		case EPIPE:
			error("%s: Connection closed by remote host", c->c_name);
			break;
		case ECONNREFUSED:
			break;
		default:
			error("read (%s): %s", c->c_name, strerror(errno));
			break;
		}
		conrecycle(s);
		return;
	}
	if (*cp != '\n' && *cp != '\r') {
		error("%s: bad greeting", c->c_name);
		confree(s);
		return;
	}
	*cp = '\0';
	if ((c->c_ssh = ssh_packet_set_connection(NULL, s, s)) == NULL)
		fatal("ssh_packet_set_connection failed");
	ssh_packet_set_timeout(c->c_ssh, timeout, 1);
	ssh_set_app_data(c->c_ssh, c);	/* back link */
	if (sscanf(buf, "SSH-%d.%d-%[^\n]\n",
	    &remote_major, &remote_minor, remote_version) == 3)
		c->c_ssh->compat = compat_datafellows(remote_version);
	else
		c->c_ssh->compat = 0;
	if (!ssh2_capable(remote_major, remote_minor)) {
		debug("%s doesn't support ssh2", c->c_name);
		confree(s);
		return;
	}
	fprintf(stderr, "%c %s:%d %s\n", print_sshfp ? ';' : '#',
	    c->c_name, ssh_port, chop(buf));
	keygrab_ssh2(c);
	confree(s);
}