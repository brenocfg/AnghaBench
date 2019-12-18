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
struct in_addr {int dummy; } ;
struct TYPE_8__ {int sin_len; int /*<<< orphan*/  sin_port; struct in_addr sin_addr; int /*<<< orphan*/  sin_family; } ;
struct TYPE_7__ {TYPE_2__ sin; } ;
struct TYPE_9__ {int length; TYPE_1__ type; } ;
typedef  TYPE_3__ isc_sockaddr_t ;
typedef  int /*<<< orphan*/  in_port_t ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  ISC_LINK_INIT (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  link ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 

void
isc_sockaddr_fromin(isc_sockaddr_t *sockaddr, const struct in_addr *ina,
		    in_port_t port)
{
	memset(sockaddr, 0, sizeof(*sockaddr));
	sockaddr->type.sin.sin_family = AF_INET;
#ifdef ISC_PLATFORM_HAVESALEN
	sockaddr->type.sin.sin_len = sizeof(sockaddr->type.sin);
#endif
	sockaddr->type.sin.sin_addr = *ina;
	sockaddr->type.sin.sin_port = htons(port);
	sockaddr->length = sizeof(sockaddr->type.sin);
	ISC_LINK_INIT(sockaddr, link);
}