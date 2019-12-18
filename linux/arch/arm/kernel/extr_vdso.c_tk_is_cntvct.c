#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_2__* clock; } ;
struct timekeeper {TYPE_3__ tkr_mono; } ;
struct TYPE_4__ {int /*<<< orphan*/  vdso_direct; } ;
struct TYPE_5__ {TYPE_1__ archdata; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_ARM_ARCH_TIMER ; 
 int /*<<< orphan*/  IS_ENABLED (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool tk_is_cntvct(const struct timekeeper *tk)
{
	if (!IS_ENABLED(CONFIG_ARM_ARCH_TIMER))
		return false;

	if (!tk->tkr_mono.clock->archdata.vdso_direct)
		return false;

	return true;
}