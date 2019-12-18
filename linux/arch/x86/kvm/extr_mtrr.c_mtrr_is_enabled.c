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
struct kvm_mtrr {int deftype; } ;

/* Variables and functions */
 int IA32_MTRR_DEF_TYPE_E ; 

__attribute__((used)) static bool mtrr_is_enabled(struct kvm_mtrr *mtrr_state)
{
	return !!(mtrr_state->deftype & IA32_MTRR_DEF_TYPE_E);
}