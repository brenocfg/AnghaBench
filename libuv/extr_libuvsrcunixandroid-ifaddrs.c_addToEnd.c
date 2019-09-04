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
struct ifaddrs {struct ifaddrs* ifa_next; } ;

/* Variables and functions */

__attribute__((used)) static void addToEnd(struct ifaddrs **p_resultList, struct ifaddrs *p_entry)
{
    if(!*p_resultList)
    {
        *p_resultList = p_entry;
    }
    else
    {
        struct ifaddrs *l_cur = *p_resultList;
        while(l_cur->ifa_next)
        {
            l_cur = l_cur->ifa_next;
        }
        l_cur->ifa_next = p_entry;
    }
}