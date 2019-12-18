#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ dpcpu_start; scalar_t__ dpcpu_stop; scalar_t__ dpcpu_curoff; int /*<<< orphan*/  dpcpu_initialized; } ;
typedef  TYPE_1__ kvm_t ;
typedef  scalar_t__ kvaddr_t ;

/* Variables and functions */

kvaddr_t
_kvm_dpcpu_validaddr(kvm_t *kd, kvaddr_t value)
{

	if (value == 0)
		return (value);

	if (!kd->dpcpu_initialized)
		return (value);

	if (value < kd->dpcpu_start || value >= kd->dpcpu_stop)
		return (value);

	return (kd->dpcpu_curoff + value);
}