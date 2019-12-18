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
typedef  int /*<<< orphan*/  ch ;

/* Variables and functions */
 int /*<<< orphan*/  CMSG_SPACE (int) ; 
 int /*<<< orphan*/  recvfd_payload (int,int*,char*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
recvfd(int sockfd, int *recv_fd)
{
	char ch = 0;

	recvfd_payload(sockfd, recv_fd, &ch, sizeof(ch),
	    CMSG_SPACE(sizeof(int)));
}