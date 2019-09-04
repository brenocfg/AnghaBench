#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct nlmsghdr {scalar_t__ nlmsg_type; scalar_t__ nlmsg_seq; scalar_t__ nlmsg_pid; } ;
struct ifaddrs {int dummy; } ;
typedef  scalar_t__ pid_t ;
struct TYPE_3__ {unsigned int m_size; struct nlmsghdr* m_data; struct TYPE_3__* m_next; } ;
typedef  TYPE_1__ NetlinkList ;

/* Variables and functions */
 scalar_t__ NLMSG_DONE ; 
 struct nlmsghdr* NLMSG_NEXT (struct nlmsghdr*,unsigned int) ; 
 scalar_t__ NLMSG_OK (struct nlmsghdr*,unsigned int) ; 
 scalar_t__ RTM_NEWLINK ; 
 int interpretLink (struct nlmsghdr*,struct ifaddrs**) ; 

__attribute__((used)) static int interpretLinks(int p_socket, pid_t p_pid, NetlinkList *p_netlinkList, struct ifaddrs **p_resultList)
{

    int l_numLinks = 0;
    for(; p_netlinkList; p_netlinkList = p_netlinkList->m_next)
    {
        unsigned int l_nlsize = p_netlinkList->m_size;
        struct nlmsghdr *l_hdr;
        for(l_hdr = p_netlinkList->m_data; NLMSG_OK(l_hdr, l_nlsize); l_hdr = NLMSG_NEXT(l_hdr, l_nlsize))
        {
            if((pid_t)l_hdr->nlmsg_pid != p_pid || (int)l_hdr->nlmsg_seq != p_socket)
            {
                continue;
            }

            if(l_hdr->nlmsg_type == NLMSG_DONE)
            {
                break;
            }

            if(l_hdr->nlmsg_type == RTM_NEWLINK)
            {
                if(interpretLink(l_hdr, p_resultList) == -1)
                {
                    return -1;
                }
                ++l_numLinks;
            }
        }
    }
    return l_numLinks;
}