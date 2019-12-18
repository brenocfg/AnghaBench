#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct in_addr {int dummy; } ;
struct TYPE_8__ {int* s6_addr; } ;
struct TYPE_9__ {int sin6_len; int /*<<< orphan*/  sin6_port; TYPE_1__ sin6_addr; int /*<<< orphan*/  sin6_family; } ;
struct TYPE_10__ {TYPE_2__ sin6; } ;
struct TYPE_11__ {int length; TYPE_3__ type; } ;
typedef  TYPE_4__ isc_sockaddr_t ;
typedef  int /*<<< orphan*/  in_port_t ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET6 ; 
 int /*<<< orphan*/  ISC_LINK_INIT (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  link ; 
 int /*<<< orphan*/  memcpy (int*,struct in_addr const*,int) ; 
 int /*<<< orphan*/  memset (TYPE_4__*,int /*<<< orphan*/ ,int) ; 

void
isc_sockaddr_v6fromin(isc_sockaddr_t *sockaddr, const struct in_addr *ina,
		      in_port_t port)
{
	memset(sockaddr, 0, sizeof(*sockaddr));
	sockaddr->type.sin6.sin6_family = AF_INET6;
#ifdef ISC_PLATFORM_HAVESALEN
	sockaddr->type.sin6.sin6_len = sizeof(sockaddr->type.sin6);
#endif
	sockaddr->type.sin6.sin6_addr.s6_addr[10] = 0xff;
	sockaddr->type.sin6.sin6_addr.s6_addr[11] = 0xff;
	memcpy(&sockaddr->type.sin6.sin6_addr.s6_addr[12], ina, 4);
	sockaddr->type.sin6.sin6_port = htons(port);
	sockaddr->length = sizeof(sockaddr->type.sin6);
	ISC_LINK_INIT(sockaddr, link);
}