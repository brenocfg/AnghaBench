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
typedef  int /*<<< orphan*/  u_char ;
struct in_addr {int dummy; } ;
struct ifnet {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  arprequest_internal (struct ifnet*,struct in_addr const*,struct in_addr const*,int /*<<< orphan*/ *) ; 

void
arprequest(struct ifnet *ifp, const struct in_addr *sip,
    const struct in_addr *tip, u_char *enaddr)
{

	(void) arprequest_internal(ifp, sip, tip, enaddr);
}