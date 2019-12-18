#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  encap; int /*<<< orphan*/  cookie; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_DEFAULT_VNET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  curvnet ; 
 int /*<<< orphan*/  in6_gif_srcaddr ; 
 int /*<<< orphan*/  ip6_encap_attach (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ip6_encap_register_srcaddr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__* ipv6_encap_cfg ; 
 int /*<<< orphan*/  ipv6_srcaddrtab ; 
 int nitems (TYPE_1__*) ; 

void
in6_gif_init(void)
{
	int i;

	if (!IS_DEFAULT_VNET(curvnet))
		return;

	ipv6_srcaddrtab = ip6_encap_register_srcaddr(in6_gif_srcaddr,
	    NULL, M_WAITOK);
	for (i = 0; i < nitems(ipv6_encap_cfg); i++)
		ipv6_encap_cfg[i].cookie = ip6_encap_attach(
		    &ipv6_encap_cfg[i].encap, NULL, M_WAITOK);
}