#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  sa; } ;
typedef  TYPE_1__ sockaddr_u ;
typedef  int SOCKET ;

/* Variables and functions */
 int /*<<< orphan*/  AF (TYPE_1__*) ; 
 int /*<<< orphan*/  SOCKLEN (TYPE_1__*) ; 
 int /*<<< orphan*/  SOCK_DGRAM ; 
 int /*<<< orphan*/  closesocket (int) ; 
 scalar_t__ connect (int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
is_reachable (sockaddr_u *dst)
{
	SOCKET sockfd;

	sockfd = socket(AF(dst), SOCK_DGRAM, 0);
	if (sockfd == -1) {
		return 0;
	}

	if (connect(sockfd, &dst->sa, SOCKLEN(dst))) {
		closesocket(sockfd);
		return 0;
	}
	closesocket(sockfd);
	return 1;
}