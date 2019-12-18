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
struct pollfd {int events; int /*<<< orphan*/  fd; } ;

/* Variables and functions */
 int POLLHUP ; 
 int POLLIN ; 
 int POLLOUT ; 
 int /*<<< orphan*/  desc ; 
 int /*<<< orphan*/  poll (struct pollfd*,int,int) ; 
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static void
child1(void)
{
	struct pollfd pfd;

	pfd.fd = desc;
	pfd.events = POLLIN | POLLHUP | POLLOUT;

	(void)poll(&pfd, 1, 2000);
	(void)printf("child1 exit\n");
}