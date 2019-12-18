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
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  ip6_encap_attach (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ip_encap_attach (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipcomp_xformsw ; 
 int /*<<< orphan*/  ipe4_cookie ; 
 int /*<<< orphan*/  ipe6_cookie ; 
 int /*<<< orphan*/  ipv4_encap_cfg ; 
 int /*<<< orphan*/  ipv6_encap_cfg ; 
 int /*<<< orphan*/  xform_attach (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ipcomp_attach(void)
{

#ifdef INET
	ipe4_cookie = ip_encap_attach(&ipv4_encap_cfg, NULL, M_WAITOK);
#endif
#ifdef INET6
	ipe6_cookie = ip6_encap_attach(&ipv6_encap_cfg, NULL, M_WAITOK);
#endif
	xform_attach(&ipcomp_xformsw);
}