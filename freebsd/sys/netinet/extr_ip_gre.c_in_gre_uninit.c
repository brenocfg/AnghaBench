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
struct gre_list {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GRE_WAIT () ; 
 scalar_t__ IS_DEFAULT_VNET (int /*<<< orphan*/ ) ; 
 struct gre_list* V_ipv4_hashtbl ; 
 scalar_t__ V_ipv4_sockets ; 
 struct gre_list* V_ipv4_srchashtbl ; 
 int /*<<< orphan*/  curvnet ; 
 int /*<<< orphan*/  ecookie ; 
 int /*<<< orphan*/  gre_hashdestroy (struct gre_list*) ; 
 int /*<<< orphan*/  ip_encap_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ip_encap_unregister_srcaddr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipv4_srcaddrtab ; 

void
in_gre_uninit(void)
{

	if (IS_DEFAULT_VNET(curvnet)) {
		ip_encap_detach(ecookie);
		ip_encap_unregister_srcaddr(ipv4_srcaddrtab);
	}
	if (V_ipv4_hashtbl != NULL) {
		gre_hashdestroy(V_ipv4_hashtbl);
		V_ipv4_hashtbl = NULL;
		GRE_WAIT();
		gre_hashdestroy(V_ipv4_srchashtbl);
		gre_hashdestroy((struct gre_list *)V_ipv4_sockets);
	}
}