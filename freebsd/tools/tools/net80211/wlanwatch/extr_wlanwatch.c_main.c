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
struct rt_msghdr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EX_OSERR ; 
 int /*<<< orphan*/  PF_ROUTE ; 
 int /*<<< orphan*/  SOCK_RAW ; 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  print_rtmsg (struct rt_msghdr*,int) ; 
 int read (int,char*,int) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
main(int argc, char *argv[])
{
	int n, s;
	char msg[2048];

	s = socket(PF_ROUTE, SOCK_RAW, 0);
	if (s < 0)
		err(EX_OSERR, "socket");
	for(;;) {
		n = read(s, msg, 2048);
		print_rtmsg((struct rt_msghdr *)msg, n);
	}
	return 0;
}