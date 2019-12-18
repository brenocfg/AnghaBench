#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  sin6_addr; } ;
struct TYPE_5__ {int /*<<< orphan*/  sin_addr; } ;
struct TYPE_4__ {int sa_family; } ;
union rsocket_address {TYPE_3__ sin6; TYPE_2__ sin; TYPE_1__ sa; } ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 
 int /*<<< orphan*/  inet_ntop (int const,int /*<<< orphan*/ *,char*,int) ; 

__attribute__((used)) static char *_ntop(union rsocket_address *rsa)
{
	static char addr[32];

	switch (rsa->sa.sa_family) {
	case AF_INET:
		inet_ntop(AF_INET, &rsa->sin.sin_addr, addr, sizeof addr);
		break;
	case AF_INET6:
		inet_ntop(AF_INET6, &rsa->sin6.sin6_addr, addr, sizeof addr);
		break;
	default:
		addr[0] = '\0';
		break;
	}

	return addr;
}