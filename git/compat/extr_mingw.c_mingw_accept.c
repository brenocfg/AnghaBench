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
struct sockaddr {int dummy; } ;
typedef  int /*<<< orphan*/  socklen_t ;
typedef  int /*<<< orphan*/  SOCKET ;

/* Variables and functions */
 int O_BINARY ; 
 int O_RDWR ; 
 int /*<<< orphan*/  _get_osfhandle (int) ; 
 int _open_osfhandle (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  accept (int /*<<< orphan*/ ,struct sockaddr*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  closesocket (int /*<<< orphan*/ ) ; 
 int errno ; 
 int error (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strerror (int) ; 

int mingw_accept(int sockfd1, struct sockaddr *sa, socklen_t *sz)
{
	int sockfd2;

	SOCKET s1 = (SOCKET)_get_osfhandle(sockfd1);
	SOCKET s2 = accept(s1, sa, sz);

	/* convert into a file descriptor */
	if ((sockfd2 = _open_osfhandle(s2, O_RDWR|O_BINARY)) < 0) {
		int err = errno;
		closesocket(s2);
		return error("unable to make a socket file descriptor: %s",
			strerror(err));
	}
	return sockfd2;
}