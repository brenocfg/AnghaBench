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
struct sockaddr_nl {int dummy; } ;
struct msghdr {int msg_namelen; int msg_iovlen; int msg_flags; scalar_t__ msg_controllen; int /*<<< orphan*/ * msg_control; struct iovec* msg_iov; void* msg_name; } ;
struct iovec {size_t iov_len; void* iov_base; } ;
typedef  int /*<<< orphan*/  l_addr ;

/* Variables and functions */
 scalar_t__ EINTR ; 
 int MSG_TRUNC ; 
 scalar_t__ errno ; 
 int recvmsg (int,struct msghdr*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int netlink_recv(int p_socket, void *p_buffer, size_t p_len)
{
    struct sockaddr_nl l_addr;
    struct msghdr l_msg;

    struct iovec l_iov;
    l_iov.iov_base = p_buffer;
    l_iov.iov_len = p_len;

    for(;;)
    {
        int l_result;
        l_msg.msg_name = (void *)&l_addr;
        l_msg.msg_namelen = sizeof(l_addr);
        l_msg.msg_iov = &l_iov;
        l_msg.msg_iovlen = 1;
        l_msg.msg_control = NULL;
        l_msg.msg_controllen = 0;
        l_msg.msg_flags = 0;
        l_result = recvmsg(p_socket, &l_msg, 0);

        if(l_result < 0)
        {
            if(errno == EINTR)
            {
                continue;
            }
            return -2;
        }

        /* Buffer was too small */
        if(l_msg.msg_flags & MSG_TRUNC)
        {
            return -1;
        }
        return l_result;
    }
}