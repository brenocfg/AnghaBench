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
 int ARM64_BP_HARDEN_NOT_REQUIRED ; 
 int ARM64_BP_HARDEN_UNKNOWN ; 
 int ARM64_BP_HARDEN_WA_NEEDED ; 
 int /*<<< orphan*/  __hardenbp_enab ; 
 scalar_t__ __spectrev2_safe ; 

int get_spectre_v2_workaround_state(void)
{
	if (__spectrev2_safe)
		return ARM64_BP_HARDEN_NOT_REQUIRED;

	if (!__hardenbp_enab)
		return ARM64_BP_HARDEN_UNKNOWN;

	return ARM64_BP_HARDEN_WA_NEEDED;
}