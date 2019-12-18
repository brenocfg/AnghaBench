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
struct TYPE_8__ {int /*<<< orphan*/  s_addr; } ;
struct TYPE_9__ {int sin_len; scalar_t__ sin_port; TYPE_1__ sin_addr; int /*<<< orphan*/  sin_family; } ;
struct TYPE_10__ {TYPE_2__ sin; } ;
struct TYPE_11__ {int length; TYPE_3__ type; } ;
typedef  TYPE_4__ isc_sockaddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  INADDR_ANY ; 
 int /*<<< orphan*/  ISC_LINK_INIT (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  link ; 
 int /*<<< orphan*/  memset (TYPE_4__*,int /*<<< orphan*/ ,int) ; 

void
isc_sockaddr_any(isc_sockaddr_t *sockaddr)
{
	memset(sockaddr, 0, sizeof(*sockaddr));
	sockaddr->type.sin.sin_family = AF_INET;
#ifdef ISC_PLATFORM_HAVESALEN
	sockaddr->type.sin.sin_len = sizeof(sockaddr->type.sin);
#endif
	sockaddr->type.sin.sin_addr.s_addr = INADDR_ANY;
	sockaddr->type.sin.sin_port = 0;
	sockaddr->length = sizeof(sockaddr->type.sin);
	ISC_LINK_INIT(sockaddr, link);
}