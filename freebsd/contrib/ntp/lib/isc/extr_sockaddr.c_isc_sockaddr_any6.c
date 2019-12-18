#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int sin6_len; scalar_t__ sin6_port; int /*<<< orphan*/  sin6_addr; int /*<<< orphan*/  sin6_family; } ;
struct TYPE_7__ {TYPE_2__ sin6; } ;
struct TYPE_9__ {int length; TYPE_1__ type; } ;
typedef  TYPE_3__ isc_sockaddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET6 ; 
 int /*<<< orphan*/  ISC_LINK_INIT (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  in6addr_any ; 
 int /*<<< orphan*/  link ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 

void
isc_sockaddr_any6(isc_sockaddr_t *sockaddr)
{
	memset(sockaddr, 0, sizeof(*sockaddr));
	sockaddr->type.sin6.sin6_family = AF_INET6;
#ifdef ISC_PLATFORM_HAVESALEN
	sockaddr->type.sin6.sin6_len = sizeof(sockaddr->type.sin6);
#endif
	sockaddr->type.sin6.sin6_addr = in6addr_any;
	sockaddr->type.sin6.sin6_port = 0;
	sockaddr->length = sizeof(sockaddr->type.sin6);
	ISC_LINK_INIT(sockaddr, link);
}