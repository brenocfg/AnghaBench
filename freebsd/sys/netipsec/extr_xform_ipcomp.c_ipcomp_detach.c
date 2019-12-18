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
 int /*<<< orphan*/  ip6_encap_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ip_encap_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipcomp_xformsw ; 
 int /*<<< orphan*/  ipe4_cookie ; 
 int /*<<< orphan*/  ipe6_cookie ; 
 int /*<<< orphan*/  xform_detach (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ipcomp_detach(void)
{

#ifdef INET
	ip_encap_detach(ipe4_cookie);
#endif
#ifdef INET6
	ip6_encap_detach(ipe6_cookie);
#endif
	xform_detach(&ipcomp_xformsw);
}