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
struct timeval {int tv_sec; scalar_t__ tv_usec; } ;
typedef  int /*<<< orphan*/  fd_set ;

/* Variables and functions */
 int /*<<< orphan*/  FD_SET (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FD_ZERO (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int select (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct timeval*) ; 

__attribute__((used)) static int socket_wait(int fd, int is_read)
{
	fd_set fds, *fdr = 0, *fdw = 0;
	struct timeval tv;
	int ret;
	tv.tv_sec = 5; tv.tv_usec = 0; // 5 seconds time out
	FD_ZERO(&fds);
	FD_SET(fd, &fds);
	if (is_read) fdr = &fds;
	else fdw = &fds;
	ret = select(fd+1, fdr, fdw, 0, &tv);
	if (ret == -1) perror("select");
	return ret;
}