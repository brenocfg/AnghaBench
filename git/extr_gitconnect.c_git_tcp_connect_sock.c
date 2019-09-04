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
struct strbuf {int /*<<< orphan*/  buf; } ;
struct addrinfo {int /*<<< orphan*/  ai_addrlen; int /*<<< orphan*/  ai_addr; int /*<<< orphan*/  ai_protocol; int /*<<< orphan*/  ai_socktype; int /*<<< orphan*/  ai_family; struct addrinfo* ai_next; } ;
typedef  int /*<<< orphan*/  hints ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  AF_INET6 ; 
 int CONNECT_IPV4 ; 
 int CONNECT_IPV6 ; 
 int CONNECT_VERBOSE ; 
 int /*<<< orphan*/  DEFAULT_GIT_PORT ; 
 int /*<<< orphan*/  IPPROTO_TCP ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 char* STR (int /*<<< orphan*/ ) ; 
 struct strbuf STRBUF_INIT ; 
 char* _ (char*) ; 
 char* ai_name (struct addrinfo*) ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ connect (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  die (char*,char*,char const*,...) ; 
 int /*<<< orphan*/  enable_keepalive (int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,...) ; 
 int /*<<< orphan*/  fprintf_ln (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  freeaddrinfo (struct addrinfo*) ; 
 int /*<<< orphan*/  gai_strerror (int) ; 
 int /*<<< orphan*/  get_host_and_port (char**,char const**) ; 
 int getaddrinfo (char*,char const*,struct addrinfo*,struct addrinfo**) ; 
 int /*<<< orphan*/  memset (struct addrinfo*,int /*<<< orphan*/ ,int) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strbuf_addf (struct strbuf*,char*,char*,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int git_tcp_connect_sock(char *host, int flags)
{
	struct strbuf error_message = STRBUF_INIT;
	int sockfd = -1;
	const char *port = STR(DEFAULT_GIT_PORT);
	struct addrinfo hints, *ai0, *ai;
	int gai;
	int cnt = 0;

	get_host_and_port(&host, &port);
	if (!*port)
		port = "<none>";

	memset(&hints, 0, sizeof(hints));
	if (flags & CONNECT_IPV4)
		hints.ai_family = AF_INET;
	else if (flags & CONNECT_IPV6)
		hints.ai_family = AF_INET6;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

	if (flags & CONNECT_VERBOSE)
		fprintf(stderr, _("Looking up %s ... "), host);

	gai = getaddrinfo(host, port, &hints, &ai);
	if (gai)
		die(_("unable to look up %s (port %s) (%s)"), host, port, gai_strerror(gai));

	if (flags & CONNECT_VERBOSE)
		/* TRANSLATORS: this is the end of "Looking up %s ... " */
		fprintf(stderr, _("done.\nConnecting to %s (port %s) ... "), host, port);

	for (ai0 = ai; ai; ai = ai->ai_next, cnt++) {
		sockfd = socket(ai->ai_family,
				ai->ai_socktype, ai->ai_protocol);
		if ((sockfd < 0) ||
		    (connect(sockfd, ai->ai_addr, ai->ai_addrlen) < 0)) {
			strbuf_addf(&error_message, "%s[%d: %s]: errno=%s\n",
				    host, cnt, ai_name(ai), strerror(errno));
			if (0 <= sockfd)
				close(sockfd);
			sockfd = -1;
			continue;
		}
		if (flags & CONNECT_VERBOSE)
			fprintf(stderr, "%s ", ai_name(ai));
		break;
	}

	freeaddrinfo(ai0);

	if (sockfd < 0)
		die(_("unable to connect to %s:\n%s"), host, error_message.buf);

	enable_keepalive(sockfd);

	if (flags & CONNECT_VERBOSE)
		/* TRANSLATORS: this is the end of "Connecting to %s (port %s) ... " */
		fprintf_ln(stderr, _("done."));

	strbuf_release(&error_message);

	return sockfd;
}