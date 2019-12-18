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

/* Variables and functions */
 int /*<<< orphan*/  IS_DEFAULT_VNET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  curvnet ; 
 int /*<<< orphan*/  ecookie ; 
 int /*<<< orphan*/  in_gre_srcaddr ; 
 int /*<<< orphan*/  ip_encap_attach (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ip_encap_register_srcaddr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipv4_encap_cfg ; 
 int /*<<< orphan*/  ipv4_srcaddrtab ; 

void
in_gre_init(void)
{

	if (!IS_DEFAULT_VNET(curvnet))
		return;
	ipv4_srcaddrtab = ip_encap_register_srcaddr(in_gre_srcaddr,
	    NULL, M_WAITOK);
	ecookie = ip_encap_attach(&ipv4_encap_cfg, NULL, M_WAITOK);
}