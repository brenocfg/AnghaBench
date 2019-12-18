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
struct timeval {int dummy; } ;
struct sockaddr {int dummy; } ;
typedef  int /*<<< orphan*/  socklen_t ;
typedef  int /*<<< orphan*/  fd_set ;

/* Variables and functions */
 int /*<<< orphan*/  ETIMEDOUT ; 
 int /*<<< orphan*/  FD_SET (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FD_ZERO (int /*<<< orphan*/ *) ; 
 int accept (int,struct sockaddr*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  errno ; 
 int select (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct timeval*) ; 

__attribute__((used)) static int
accept_with_timeout(int socket,
		    struct sockaddr *address,
		    socklen_t *address_len,
		    struct timeval *timeout)
{
    int ret;
    fd_set rfd;
    FD_ZERO(&rfd);
    FD_SET(socket, &rfd);
    ret = select(socket + 1, &rfd, NULL, NULL, timeout);
    if(ret < 0)
	return ret;
    if(ret == 0) {
	errno = ETIMEDOUT;
	return -1;
    }
    return accept(socket, address, address_len);
}