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
struct sockaddr_ll {size_t sll_halen; int /*<<< orphan*/ * sll_addr; } ;
struct sockaddr_in6 {int /*<<< orphan*/  sin6_addr; } ;
struct sockaddr_in {int /*<<< orphan*/  sin_addr; } ;
struct sockaddr {int sa_family; int /*<<< orphan*/ * sa_data; } ;
typedef  int sa_family_t ;

/* Variables and functions */
#define  AF_INET 130 
#define  AF_INET6 129 
#define  AF_PACKET 128 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,void*,size_t) ; 

__attribute__((used)) static void makeSockaddr(sa_family_t p_family, struct sockaddr *p_dest, void *p_data, size_t p_size)
{
    switch(p_family)
    {
        case AF_INET:
            memcpy(&((struct sockaddr_in*)p_dest)->sin_addr, p_data, p_size);
            break;
        case AF_INET6:
            memcpy(&((struct sockaddr_in6*)p_dest)->sin6_addr, p_data, p_size);
            break;
        case AF_PACKET:
            memcpy(((struct sockaddr_ll*)p_dest)->sll_addr, p_data, p_size);
            ((struct sockaddr_ll*)p_dest)->sll_halen = p_size;
            break;
        default:
            memcpy(p_dest->sa_data, p_data, p_size);
            break;
    }
    p_dest->sa_family = p_family;
}