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
 int /*<<< orphan*/  alg_check_test_descs_order () ; 
 int /*<<< orphan*/  alg_check_testvec_configs () ; 
 int /*<<< orphan*/  pr_warn (char*) ; 

__attribute__((used)) static void testmgr_onetime_init(void)
{
	alg_check_test_descs_order();
	alg_check_testvec_configs();

#ifdef CONFIG_CRYPTO_MANAGER_EXTRA_TESTS
	pr_warn("alg: extra crypto tests enabled.  This is intended for developer use only.\n");
#endif
}