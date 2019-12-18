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
struct pollfd {int fd; int /*<<< orphan*/  events; } ;
struct message {size_t seq; } ;
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  socklen_t ;
typedef  int /*<<< orphan*/  msg ;

/* Variables and functions */
 int /*<<< orphan*/  ERRX (int /*<<< orphan*/ ,char*,size_t,...) ; 
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  POLLIN ; 
 int /*<<< orphan*/  bind ; 
 scalar_t__ debug ; 
 int /*<<< orphan*/  errno ; 
 int getsocket (char const*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int poll (struct pollfd*,int,int) ; 
 int recv (int,struct message*,int,int /*<<< orphan*/ ) ; 
 int recvfrom (int,struct message*,int,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  show (char*,struct message*) ; 
 int /*<<< orphan*/  ss ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  synchronize (int const,int) ; 

__attribute__((used)) static void
receiver(const int fd, const char *host, const char *port, size_t n, bool conn,
    bool bug)
{
	int s;
	ssize_t l;
	size_t seq;
	struct message msg;
	struct pollfd pfd;
	socklen_t slen;

	s = getsocket(host, port, bind, &slen, bug);
	pfd.fd = s;
	pfd.events = POLLIN;

	/* Tell I'm ready */
	synchronize(fd, false);

	for (seq = 0; seq < n; seq++) {
		if (poll(&pfd, 1, 10000) == -1)
			ERRX(EXIT_FAILURE, "poll (%s)", strerror(errno));
		l = conn ? recv(s, &msg, sizeof(msg), 0) :
		    recvfrom(s, &msg, sizeof(msg), 0, (void *)&ss, &slen);
		if (l == -1)
			ERRX(EXIT_FAILURE, "recv (%s)", strerror(errno));
		if (debug)
			show("got", &msg);
		if (seq != msg.seq)
			ERRX(EXIT_FAILURE, "seq: expect=%zu actual=%zu",
			    seq, msg.seq);
	}

	/* Tell I'm finished */
	synchronize(fd, false);
}