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
struct sockaddr_in6 {int /*<<< orphan*/  sin6_scope_id; } ;
struct sockaddr {scalar_t__ sa_family; } ;
struct rtattr {int rta_type; } ;
struct nlmsghdr {int dummy; } ;
struct in6_addr {int dummy; } ;
struct ifaddrs {char* ifa_name; struct sockaddr* ifa_netmask; struct sockaddr* ifa_addr; struct sockaddr* ifa_broadaddr; struct sockaddr* ifa_dstaddr; int /*<<< orphan*/  ifa_flags; } ;
struct ifaddrmsg {scalar_t__ ifa_family; unsigned int ifa_prefixlen; int /*<<< orphan*/  ifa_index; int /*<<< orphan*/  ifa_flags; } ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 scalar_t__ AF_INET6 ; 
 scalar_t__ AF_PACKET ; 
#define  IFA_ADDRESS 131 
#define  IFA_BROADCAST 130 
#define  IFA_LABEL 129 
#define  IFA_LOCAL 128 
 struct rtattr* IFA_RTA (struct ifaddrmsg*) ; 
 int /*<<< orphan*/  IN6_IS_ADDR_LINKLOCAL (struct in6_addr*) ; 
 int /*<<< orphan*/  IN6_IS_ADDR_MC_LINKLOCAL (struct in6_addr*) ; 
 size_t NLMSG_ALIGN (size_t) ; 
 scalar_t__ NLMSG_DATA (struct nlmsghdr*) ; 
 size_t NLMSG_PAYLOAD (struct nlmsghdr*,int) ; 
 void* RTA_DATA (struct rtattr*) ; 
 struct rtattr* RTA_NEXT (struct rtattr*,size_t) ; 
 scalar_t__ RTA_OK (struct rtattr*,size_t) ; 
 size_t RTA_PAYLOAD (struct rtattr*) ; 
 int /*<<< orphan*/  addToEnd (struct ifaddrs**,struct ifaddrs*) ; 
 size_t calcAddrLen (scalar_t__,size_t) ; 
 struct ifaddrs* findInterface (int /*<<< orphan*/ ,struct ifaddrs**,int) ; 
 int /*<<< orphan*/  makeSockaddr (scalar_t__,struct sockaddr*,unsigned char*,unsigned int) ; 
 int /*<<< orphan*/  memset (struct ifaddrs*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strncpy (char*,void*,size_t) ; 
 struct ifaddrs* uv__malloc (int) ; 

__attribute__((used)) static int interpretAddr(struct nlmsghdr *p_hdr, struct ifaddrs **p_resultList, int p_numLinks)
{
    struct ifaddrmsg *l_info = (struct ifaddrmsg *)NLMSG_DATA(p_hdr);
    struct ifaddrs *l_interface = findInterface(l_info->ifa_index, p_resultList, p_numLinks);

    size_t l_nameSize = 0;
    size_t l_addrSize = 0;

    int l_addedNetmask = 0;

    size_t l_rtaSize = NLMSG_PAYLOAD(p_hdr, sizeof(struct ifaddrmsg));
    struct rtattr *l_rta;
    struct ifaddrs *l_entry;

    char *l_name;
    char *l_addr;

    for(l_rta = IFA_RTA(l_info); RTA_OK(l_rta, l_rtaSize); l_rta = RTA_NEXT(l_rta, l_rtaSize))
    {
        size_t l_rtaDataSize = RTA_PAYLOAD(l_rta);
        if(l_info->ifa_family == AF_PACKET)
        {
            continue;
        }

        switch(l_rta->rta_type)
        {
            case IFA_ADDRESS:
            case IFA_LOCAL:
                if((l_info->ifa_family == AF_INET || l_info->ifa_family == AF_INET6) && !l_addedNetmask)
                {
                    /* Make room for netmask */
                    l_addrSize += NLMSG_ALIGN(calcAddrLen(l_info->ifa_family, l_rtaDataSize));
                    l_addedNetmask = 1;
                }
		break;
            case IFA_BROADCAST:
                l_addrSize += NLMSG_ALIGN(calcAddrLen(l_info->ifa_family, l_rtaDataSize));
                break;
            case IFA_LABEL:
                l_nameSize += NLMSG_ALIGN(l_rtaDataSize + 1);
                break;
            default:
                break;
        }
    }

    l_entry = uv__malloc(sizeof(struct ifaddrs) + l_nameSize + l_addrSize);
    if (l_entry == NULL)
    {
        return -1;
    }
    memset(l_entry, 0, sizeof(struct ifaddrs));
    l_entry->ifa_name = (l_interface ? l_interface->ifa_name : "");

    l_name = ((char *)l_entry) + sizeof(struct ifaddrs);
    l_addr = l_name + l_nameSize;

    l_entry->ifa_flags = l_info->ifa_flags;
    if(l_interface)
    {
        l_entry->ifa_flags |= l_interface->ifa_flags;
    }

    l_rtaSize = NLMSG_PAYLOAD(p_hdr, sizeof(struct ifaddrmsg));
    for(l_rta = IFA_RTA(l_info); RTA_OK(l_rta, l_rtaSize); l_rta = RTA_NEXT(l_rta, l_rtaSize))
    {
        void *l_rtaData = RTA_DATA(l_rta);
        size_t l_rtaDataSize = RTA_PAYLOAD(l_rta);
        switch(l_rta->rta_type)
        {
            case IFA_ADDRESS:
            case IFA_BROADCAST:
            case IFA_LOCAL:
            {
                size_t l_addrLen = calcAddrLen(l_info->ifa_family, l_rtaDataSize);
                makeSockaddr(l_info->ifa_family, (struct sockaddr *)l_addr, l_rtaData, l_rtaDataSize);
                if(l_info->ifa_family == AF_INET6)
                {
                    if(IN6_IS_ADDR_LINKLOCAL((struct in6_addr *)l_rtaData) || IN6_IS_ADDR_MC_LINKLOCAL((struct in6_addr *)l_rtaData))
                    {
                        ((struct sockaddr_in6 *)l_addr)->sin6_scope_id = l_info->ifa_index;
                    }
                }

                /* Apparently in a point-to-point network IFA_ADDRESS contains
                 * the dest address and IFA_LOCAL contains the local address
                 */
                if(l_rta->rta_type == IFA_ADDRESS)
                {
                    if(l_entry->ifa_addr)
                    {
                        l_entry->ifa_dstaddr = (struct sockaddr *)l_addr;
                    }
                    else
                    {
                        l_entry->ifa_addr = (struct sockaddr *)l_addr;
                    }
                }
                else if(l_rta->rta_type == IFA_LOCAL)
                {
                    if(l_entry->ifa_addr)
                    {
                        l_entry->ifa_dstaddr = l_entry->ifa_addr;
                    }
                    l_entry->ifa_addr = (struct sockaddr *)l_addr;
                }
                else
                {
                    l_entry->ifa_broadaddr = (struct sockaddr *)l_addr;
                }
                l_addr += NLMSG_ALIGN(l_addrLen);
                break;
            }
            case IFA_LABEL:
                strncpy(l_name, l_rtaData, l_rtaDataSize);
                l_name[l_rtaDataSize] = '\0';
                l_entry->ifa_name = l_name;
                break;
            default:
                break;
        }
    }

    if(l_entry->ifa_addr && (l_entry->ifa_addr->sa_family == AF_INET || l_entry->ifa_addr->sa_family == AF_INET6))
    {
        unsigned l_maxPrefix = (l_entry->ifa_addr->sa_family == AF_INET ? 32 : 128);
        unsigned l_prefix = (l_info->ifa_prefixlen > l_maxPrefix ? l_maxPrefix : l_info->ifa_prefixlen);
        unsigned char l_mask[16] = {0};
        unsigned i;
        for(i=0; i<(l_prefix/8); ++i)
        {
            l_mask[i] = 0xff;
        }
        if(l_prefix % 8)
        {
            l_mask[i] = 0xff << (8 - (l_prefix % 8));
        }

        makeSockaddr(l_entry->ifa_addr->sa_family, (struct sockaddr *)l_addr, l_mask, l_maxPrefix / 8);
        l_entry->ifa_netmask = (struct sockaddr *)l_addr;
    }

    addToEnd(p_resultList, l_entry);
    return 0;
}