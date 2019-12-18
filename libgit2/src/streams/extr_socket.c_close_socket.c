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
typedef  scalar_t__ GIT_SOCKET ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ERROR_OS ; 
 scalar_t__ INVALID_SOCKET ; 
 scalar_t__ SOCKET_ERROR ; 
 scalar_t__ WSACleanup () ; 
 int close (scalar_t__) ; 
 scalar_t__ closesocket (scalar_t__) ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int close_socket(GIT_SOCKET s)
{
	if (s == INVALID_SOCKET)
		return 0;

#ifdef GIT_WIN32
	if (SOCKET_ERROR == closesocket(s))
		return -1;

	if (0 != WSACleanup()) {
		git_error_set(GIT_ERROR_OS, "winsock cleanup failed");
		return -1;
	}

	return 0;
#else
	return close(s);
#endif

}