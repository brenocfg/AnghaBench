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
struct timeval {int tv_usec; int /*<<< orphan*/  tv_sec; } ;
struct TYPE_2__ {int tv_nsec; int /*<<< orphan*/  tv_sec; } ;
struct message {size_t seq; TYPE_1__ ts; } ;
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  socklen_t ;
typedef  int /*<<< orphan*/  msg ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_MONOTONIC ; 
 int /*<<< orphan*/  ERRX (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int clock_gettime (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  connect ; 
 int /*<<< orphan*/  connector ; 
 scalar_t__ debug ; 
 int /*<<< orphan*/  errno ; 
 int getsocket (char const*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int gettimeofday (struct timeval*,int /*<<< orphan*/ *) ; 
 int send (int,struct message*,int,int /*<<< orphan*/ ) ; 
 int sendto (int,struct message*,int,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  show (char*,struct message*) ; 
 int /*<<< orphan*/  ss ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int synchronize (int const,int) ; 
 int /*<<< orphan*/  usleep (int) ; 

__attribute__((used)) static int
sender(const int fd, const char *host, const char *port, size_t n, bool conn,
    bool bug)
{
	int s;
	ssize_t l;
	struct message msg;

	socklen_t slen;

	s = getsocket(host, port, conn ? connect : connector, &slen, bug);

	/* Wait until receiver gets ready. */
	if (synchronize(fd, true) == -1)
		return -1;

	for (msg.seq = 0; msg.seq < n; msg.seq++) {
#ifdef CLOCK_MONOTONIC
		if (clock_gettime(CLOCK_MONOTONIC, &msg.ts) == -1)
			ERRX(EXIT_FAILURE, "clock (%s)", strerror(errno));
#else
		struct timeval tv;
		if (gettimeofday(&tv, NULL) == -1)
			ERRX(EXIT_FAILURE, "clock (%s)", strerror(errno));
		msg.ts.tv_sec = tv.tv_sec;
		msg.ts.tv_nsec = tv.tv_usec * 1000;
#endif
		if (debug)
			show("sending", &msg);
		l = conn ? send(s, &msg, sizeof(msg), 0) :
		    sendto(s, &msg, sizeof(msg), 0, (void *)&ss, slen);
		if (l == -1)
			ERRX(EXIT_FAILURE, "send (%s)", strerror(errno));
		usleep(100);
	}

	/* Wait until receiver finishes its work. */
	if (synchronize(fd, true) == -1)
		return -1;

	return 0;
}