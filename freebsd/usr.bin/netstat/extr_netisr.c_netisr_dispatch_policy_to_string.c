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
typedef  int u_int ;

/* Variables and functions */
#define  NETISR_DISPATCH_DEFAULT 131 
#define  NETISR_DISPATCH_DEFERRED 130 
#define  NETISR_DISPATCH_DIRECT 129 
#define  NETISR_DISPATCH_HYBRID 128 
 int /*<<< orphan*/  snprintf (char*,size_t,char*,char const*) ; 

__attribute__((used)) static void
netisr_dispatch_policy_to_string(u_int policy, char *buf,
    size_t buflen)
{
	const char *str;

	switch (policy) {
	case NETISR_DISPATCH_DEFAULT:
		str = "default";
		break;
	case NETISR_DISPATCH_DEFERRED:
		str = "deferred";
		break;
	case NETISR_DISPATCH_HYBRID:
		str = "hybrid";
		break;
	case NETISR_DISPATCH_DIRECT:
		str = "direct";
		break;
	default:
		str = "unknown";
		break;
	}
	snprintf(buf, buflen, "%s", str);
}