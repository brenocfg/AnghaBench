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
 int /*<<< orphan*/ * V_ipv4_hashtbl ; 
 int /*<<< orphan*/ * V_ipv4_srchashtbl ; 
 int /*<<< orphan*/  curvnet ; 
 int /*<<< orphan*/  gif_hashdestroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ip_encap_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ip_encap_unregister_srcaddr (int /*<<< orphan*/ ) ; 
 TYPE_1__* ipv4_encap_cfg ; 
 int /*<<< orphan*/  ipv4_srcaddrtab ; 
 int nitems (TYPE_1__*) ; 

void
in_gif_uninit(void)
{
	int i;

	if (IS_DEFAULT_VNET(curvnet)) {
		for (i = 0; i < nitems(ipv4_encap_cfg); i++)
			ip_encap_detach(ipv4_encap_cfg[i].cookie);
		ip_encap_unregister_srcaddr(ipv4_srcaddrtab);
	}
	if (V_ipv4_hashtbl != NULL) {
		gif_hashdestroy(V_ipv4_hashtbl);
		V_ipv4_hashtbl = NULL;
		GIF_WAIT();
		gif_hashdestroy(V_ipv4_srchashtbl);
	}
}