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
 int /*<<< orphan*/  CONFIG_IMA_ARCH_POLICY ; 
 int /*<<< orphan*/  CONFIG_MODULE_SIG ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 scalar_t__ arch_ima_get_secureboot () ; 
 char const* const* sb_arch_rules ; 
 int /*<<< orphan*/  set_module_sig_enforced () ; 

const char * const *arch_get_ima_policy(void)
{
	if (IS_ENABLED(CONFIG_IMA_ARCH_POLICY) && arch_ima_get_secureboot()) {
		if (IS_ENABLED(CONFIG_MODULE_SIG))
			set_module_sig_enforced();
		return sb_arch_rules;
	}
	return NULL;
}