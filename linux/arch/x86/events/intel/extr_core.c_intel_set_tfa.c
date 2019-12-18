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
typedef  scalar_t__ u64 ;
struct cpu_hw_events {scalar_t__ tfa_shadow; } ;

/* Variables and functions */
 scalar_t__ MSR_TFA_RTM_FORCE_ABORT ; 
 int /*<<< orphan*/  MSR_TSX_FORCE_ABORT ; 
 int /*<<< orphan*/  wrmsrl (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void intel_set_tfa(struct cpu_hw_events *cpuc, bool on)
{
	u64 val = on ? MSR_TFA_RTM_FORCE_ABORT : 0;

	if (cpuc->tfa_shadow != val) {
		cpuc->tfa_shadow = val;
		wrmsrl(MSR_TSX_FORCE_ABORT, val);
	}
}