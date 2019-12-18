#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct vdso_timehands {int /*<<< orphan*/  th_res; int /*<<< orphan*/  th_physical; int /*<<< orphan*/  th_algo; } ;
struct timecounter {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  physical; } ;

/* Variables and functions */
 int /*<<< orphan*/  VDSO_TH_ALGO_ARM_GENTIM ; 
 TYPE_1__* arm_tmr_sc ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static uint32_t
arm_tmr_fill_vdso_timehands(struct vdso_timehands *vdso_th,
    struct timecounter *tc)
{

	vdso_th->th_algo = VDSO_TH_ALGO_ARM_GENTIM;
	vdso_th->th_physical = arm_tmr_sc->physical;
	bzero(vdso_th->th_res, sizeof(vdso_th->th_res));
	return (1);
}