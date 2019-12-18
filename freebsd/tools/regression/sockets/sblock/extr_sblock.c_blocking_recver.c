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
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  ch ;

/* Variables and functions */
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  errx (int,char*,...) ; 
 scalar_t__ interrupted ; 
 int recv (int,char*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
blocking_recver(int fd)
{
	ssize_t len;
	char ch;

	len = recv(fd, &ch, sizeof(ch), 0);
	if (len < 0)
		err(-1, "FAIL: blocking_recver: recv");
	if (len == 0)
		errx(-1, "FAIL: blocking_recver: recv: eof");
	if (len != 1)
		errx(-1, "FAIL: blocking_recver: recv: %zd bytes", len);
	if (interrupted)
		errx(-1, "FAIL: blocking_recver: interrupted wrong pid");
}