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
struct kevent {int dummy; } ;
struct dcons_state {int /*<<< orphan*/  to; int /*<<< orphan*/  kq; int /*<<< orphan*/  zero; int /*<<< orphan*/  traw; int /*<<< orphan*/  tsave; struct dcons_port* port; } ;
struct dcons_port {int port; int sport; int infd; int outfd; int s; struct addrinfo* res; } ;
struct addrinfo {int /*<<< orphan*/  ai_addrlen; int /*<<< orphan*/  ai_addr; scalar_t__ ai_protocol; int /*<<< orphan*/  ai_socktype; int /*<<< orphan*/  ai_family; int /*<<< orphan*/  ai_flags; } ;
typedef  int /*<<< orphan*/  service ;
typedef  int /*<<< orphan*/  on ;
typedef  int /*<<< orphan*/  hints ;

/* Variables and functions */
 int /*<<< orphan*/  AI_PASSIVE ; 
 int /*<<< orphan*/  EVFILT_READ ; 
 int EV_ADD ; 
 int EV_ONESHOT ; 
 int /*<<< orphan*/  EV_SET (struct kevent*,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,void*) ; 
 int /*<<< orphan*/  NOTE_LOWAT ; 
 int /*<<< orphan*/  PF_INET ; 
 int /*<<< orphan*/  PF_UNSPEC ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SO_REUSEADDR ; 
 int STDIN_FILENO ; 
 int STDOUT_FILENO ; 
 int /*<<< orphan*/  TCSADRAIN ; 
 scalar_t__ bind (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cfmakeraw (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  errx (int,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gai_strerror (int) ; 
 int getaddrinfo (char*,char*,struct addrinfo*,struct addrinfo**) ; 
 int kevent (int /*<<< orphan*/ ,struct kevent*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ listen (int,int) ; 
 int /*<<< orphan*/  memset (struct addrinfo*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*,char*,int,int) ; 
 int /*<<< orphan*/  setsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int tc_set ; 
 scalar_t__ tcgetattr (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tcsetattr (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ verbose ; 

__attribute__((used)) static void
dconschat_init_socket(struct dcons_state *dc, int port, char *host, int sport)
{
	struct addrinfo hints, *res;
	int on = 1, error;
	char service[10];
	struct kevent kev;
	struct dcons_port *p;

	p = &dc->port[port];
	p->port = port;
	p->sport = sport;
	p->infd = p->outfd = -1;

	if (sport < 0)
		return;

	if (sport == 0) {

		/* Use stdin and stdout */
		p->infd = STDIN_FILENO;
		p->outfd = STDOUT_FILENO;
		p->s = -1;
		if (tc_set == 0 &&
		    tcgetattr(STDIN_FILENO, &dc->tsave) == 0) {
			dc->traw = dc->tsave;
			cfmakeraw(&dc->traw);
			tcsetattr(STDIN_FILENO, TCSADRAIN, &dc->traw);
			tc_set = 1;
		}
		EV_SET(&kev, p->infd, EVFILT_READ, EV_ADD, NOTE_LOWAT, 1,
		    (void *)p);
		kevent(dc->kq, &kev, 1, NULL, 0, &dc->zero);
		return;
	}

	memset(&hints, 0, sizeof(hints));
	hints.ai_flags = AI_PASSIVE;
#if 1	/* gdb can talk v4 only */
	hints.ai_family = PF_INET;
#else
	hints.ai_family = PF_UNSPEC;
#endif
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = 0;

	if (verbose)
		printf("%s:%d for port %d\n",
			host == NULL ? "*" : host, sport, port);
	snprintf(service, sizeof(service), "%d", sport);
	error = getaddrinfo(host, service,  &hints, &res);
	if (error)
		errx(1, "tcp/%s: %s\n", service, gai_strerror(error));
	p->res = res;
	p->s = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
	if (p->s < 0)
		err(1, "socket");
	setsockopt(p->s, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));

	if (bind(p->s, p->res->ai_addr, p->res->ai_addrlen) < 0) {
		err(1, "bind");
	}
	if (listen(p->s, 1) < 0)
		err(1, "listen");
	EV_SET(&kev, p->s, EVFILT_READ, EV_ADD | EV_ONESHOT, 0, 0, (void *)p);
	error = kevent(dc->kq, &kev, 1, NULL, 0, &dc->to);
	if (error < 0)
		err(1, "kevent");
	return;
}