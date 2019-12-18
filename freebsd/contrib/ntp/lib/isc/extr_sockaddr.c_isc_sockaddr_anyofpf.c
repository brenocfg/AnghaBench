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
typedef  int /*<<< orphan*/  isc_sockaddr_t ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 
 int /*<<< orphan*/  INSIST (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isc_sockaddr_any (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  isc_sockaddr_any6 (int /*<<< orphan*/ *) ; 

void
isc_sockaddr_anyofpf(isc_sockaddr_t *sockaddr, int pf) {
     switch (pf) {
     case AF_INET:
	     isc_sockaddr_any(sockaddr);
	     break;
     case AF_INET6:
	     isc_sockaddr_any6(sockaddr);
	     break;
     default:
	     INSIST(0);
     }
}