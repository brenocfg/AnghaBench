#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct addrinfo {TYPE_1__* ai_addr; int /*<<< orphan*/  ai_family; int /*<<< orphan*/  ai_addrlen; } ;
struct TYPE_4__ {int /*<<< orphan*/  sa_family; } ;
struct TYPE_5__ {TYPE_1__ sa; } ;
typedef  TYPE_2__ sockaddr_u ;

/* Variables and functions */
 int /*<<< orphan*/  SIZEOF_SOCKADDR (int /*<<< orphan*/ ) ; 

struct addrinfo
CreateAddrinfo(sockaddr_u* sock) {
	struct addrinfo a;
	a.ai_family = sock->sa.sa_family;
	a.ai_addrlen = SIZEOF_SOCKADDR(a.ai_family);
	a.ai_addr = &sock->sa;
	return a;
}