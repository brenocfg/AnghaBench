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
 int EBUSY ; 
 scalar_t__ icl_ncons ; 
 int /*<<< orphan*/  icl_pdu_zone ; 
 int /*<<< orphan*/  icl_unregister (char*,int) ; 
 int /*<<< orphan*/  uma_zdestroy (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
icl_soft_unload(void)
{

	if (icl_ncons != 0)
		return (EBUSY);

	icl_unregister("none", false);
#if defined(ICL_KERNEL_PROXY) && 0
	icl_unregister("proxytest", true);
#endif

	uma_zdestroy(icl_pdu_zone);

	return (0);
}