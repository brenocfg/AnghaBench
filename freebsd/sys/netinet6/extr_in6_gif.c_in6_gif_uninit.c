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
struct TYPE_3__ {int /*<<< orphan*/  cookie; } ;

/* Variables and functions */
 int /*<<< orphan*/  GIF_WAIT () ; 
 scalar_t__ IS_DEFAULT_VNET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * V_ipv6_hashtbl ; 
 int /*<<< orphan*/ * V_ipv6_srchashtbl ; 
 int /*<<< orphan*/  curvnet ; 
 int /*<<< orphan*/  gif_hashdestroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ip6_encap_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ip6_encap_unregister_srcaddr (int /*<<< orphan*/ ) ; 
 TYPE_1__* ipv6_encap_cfg ; 
 int /*<<< orphan*/  ipv6_srcaddrtab ; 
 int nitems (TYPE_1__*) ; 

void
in6_gif_uninit(void)
{
	int i;

	if (IS_DEFAULT_VNET(curvnet)) {
		for (i = 0; i < nitems(ipv6_encap_cfg); i++)
			ip6_encap_detach(ipv6_encap_cfg[i].cookie);
		ip6_encap_unregister_srcaddr(ipv6_srcaddrtab);
	}
	if (V_ipv6_hashtbl != NULL) {
		gif_hashdestroy(V_ipv6_hashtbl);
		V_ipv6_hashtbl = NULL;
		GIF_WAIT();
		gif_hashdestroy(V_ipv6_srchashtbl);
	}
}