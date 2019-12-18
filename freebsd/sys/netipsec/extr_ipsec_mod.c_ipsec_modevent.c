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
typedef  int /*<<< orphan*/  module_t ;

/* Variables and functions */
 int ENOMEM ; 
 int EOPNOTSUPP ; 
#define  MOD_LOAD 129 
#define  MOD_UNLOAD 128 
 int /*<<< orphan*/  ipsec_initialized () ; 
 int /*<<< orphan*/  ipsec_support_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipsec_support_enable (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ipv4_ipsec_support ; 
 int /*<<< orphan*/  ipv4_methods ; 
 int /*<<< orphan*/  ipv6_ipsec_support ; 
 int /*<<< orphan*/  ipv6_methods ; 

__attribute__((used)) static int
ipsec_modevent(module_t mod, int type, void *data)
{

	switch (type) {
	case MOD_LOAD:
		/* All xforms are registered via SYSINIT */
		if (!ipsec_initialized())
			return (ENOMEM);
#ifdef KLD_MODULE
#ifdef INET
		ipsec_support_enable(ipv4_ipsec_support, &ipv4_methods);
#endif
#ifdef INET6
		ipsec_support_enable(ipv6_ipsec_support, &ipv6_methods);
#endif
#endif /* KLD_MODULE */
		break;
	case MOD_UNLOAD:
		/* All xforms are unregistered via SYSUNINIT */
#ifdef KLD_MODULE
#ifdef INET
		ipsec_support_disable(ipv4_ipsec_support);
#endif
#ifdef INET6
		ipsec_support_disable(ipv6_ipsec_support);
#endif
#endif /* KLD_MODULE */
		break;
	default:
		return (EOPNOTSUPP);
	}
	return (0);
}