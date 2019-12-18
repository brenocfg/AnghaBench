#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct sockaddr_in6 {int dummy; } ;
struct sockaddr_in {int dummy; } ;
struct sockaddr {int sa_family; } ;
struct TYPE_5__ {int sa_family; } ;
struct TYPE_6__ {struct sockaddr_in6 sin6; struct sockaddr_in sin; TYPE_1__ sa; } ;
typedef  TYPE_2__ quicly_address_t ;

/* Variables and functions */
#define  AF_INET 130 
#define  AF_INET6 129 
#define  AF_UNSPEC 128 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int,int) ; 

__attribute__((used)) static void set_address(quicly_address_t *addr, struct sockaddr *sa)
{
    if (sa == NULL) {
        addr->sa.sa_family = AF_UNSPEC;
        return;
    }

    switch (sa->sa_family) {
    case AF_UNSPEC:
        addr->sa.sa_family = AF_UNSPEC;
        break;
    case AF_INET:
        addr->sin = *(struct sockaddr_in *)sa;
        break;
    case AF_INET6:
        addr->sin6 = *(struct sockaddr_in6 *)sa;
        break;
    default:
        memset(addr, 0xff, sizeof(*addr));
        assert(!"unexpected address type");
        break;
    }
}