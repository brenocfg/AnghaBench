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
typedef  int /*<<< orphan*/  SOCKET ;

/* Variables and functions */
 int /*<<< orphan*/  _get_osfhandle (int) ; 
 int listen (int /*<<< orphan*/ ,int) ; 

int mingw_listen(int sockfd, int backlog)
{
	SOCKET s = (SOCKET)_get_osfhandle(sockfd);
	return listen(s, backlog);
}