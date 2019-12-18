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
typedef  int /*<<< orphan*/  uintmax_t ;
typedef  int u_int64_t ;
struct TYPE_2__ {int /*<<< orphan*/  s_addr; } ;
struct sockaddr_in {int sin_len; int /*<<< orphan*/  sin_port; TYPE_1__ sin_addr; int /*<<< orphan*/  sin_family; } ;
typedef  int /*<<< orphan*/  sin ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  PORT ; 
 int SECONDS ; 
 int /*<<< orphan*/  SIGALRM ; 
 scalar_t__ SIG_ERR ; 
 int /*<<< orphan*/  alarm (int) ; 
 int /*<<< orphan*/  alarm_handler ; 
 int /*<<< orphan*/  bzero (struct sockaddr_in*,int) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inet_addr (char*) ; 
 int /*<<< orphan*/  printf (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timer_fired ; 
 scalar_t__ try_connect (struct sockaddr_in*) ; 

int
main(int argc, char *argv[])
{
	struct sockaddr_in sin;
	u_int64_t counter;

	if (argc != 2)
		errx(-1, "usage: tcpconnect [ip]");

	bzero(&sin, sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_len = sizeof(sin);
	sin.sin_addr.s_addr = inet_addr(argv[1]);
	sin.sin_port = htons(PORT);

	if (signal(SIGALRM, alarm_handler) == SIG_ERR)
		err(-1, "signal(SIGALRM)");

	alarm(SECONDS);

	counter = 0;
	while (!timer_fired) {
		if (try_connect(&sin) == 0)
			counter++;
	}
	printf("%ju count\n", (uintmax_t)counter);
	printf("%ju connections/second\n", (uintmax_t)(counter / SECONDS));

	return (0);
}