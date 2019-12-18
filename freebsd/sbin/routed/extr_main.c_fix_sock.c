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
typedef  int /*<<< orphan*/  rbuf ;
typedef  int /*<<< orphan*/  on ;

/* Variables and functions */
 int /*<<< orphan*/  F_SETFL ; 
 int MIN_SOCKBUF ; 
 int /*<<< orphan*/  O_NONBLOCK ; 
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SO_BROADCAST ; 
 int /*<<< orphan*/  SO_PASSIFNAME ; 
 int /*<<< orphan*/  SO_RCVBUF ; 
 int /*<<< orphan*/  errno ; 
 int fcntl (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  logbad (int,char*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msglog (char*,char const*,int,...) ; 
 scalar_t__ setsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_act (char*,int) ; 

void
fix_sock(int sock,
	 const char *name)
{
	int on;
#define MIN_SOCKBUF (4*1024)
	static int rbuf;

	if (fcntl(sock, F_SETFL, O_NONBLOCK) == -1)
		logbad(1, "fcntl(%s) O_NONBLOCK: %s",
		       name, strerror(errno));
	on = 1;
	if (setsockopt(sock, SOL_SOCKET,SO_BROADCAST, &on,sizeof(on)) < 0)
		msglog("setsockopt(%s,SO_BROADCAST): %s",
		       name, strerror(errno));
#ifdef USE_PASSIFNAME
	on = 1;
	if (setsockopt(sock, SOL_SOCKET, SO_PASSIFNAME, &on,sizeof(on)) < 0)
		msglog("setsockopt(%s,SO_PASSIFNAME): %s",
		       name, strerror(errno));
#endif

	if (rbuf >= MIN_SOCKBUF) {
		if (setsockopt(sock, SOL_SOCKET, SO_RCVBUF,
			       &rbuf, sizeof(rbuf)) < 0)
			msglog("setsockopt(%s,SO_RCVBUF=%d): %s",
			       name, rbuf, strerror(errno));
	} else {
		for (rbuf = 60*1024; ; rbuf -= 4096) {
			if (setsockopt(sock, SOL_SOCKET, SO_RCVBUF,
				       &rbuf, sizeof(rbuf)) == 0) {
				trace_act("RCVBUF=%d", rbuf);
				break;
			}
			if (rbuf < MIN_SOCKBUF) {
				msglog("setsockopt(%s,SO_RCVBUF = %d): %s",
				       name, rbuf, strerror(errno));
				break;
			}
		}
	}
}