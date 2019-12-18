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
typedef  int uint32_t ;
struct vdso_timehands {int th_x86_shift; int th_x86_hpet_idx; int /*<<< orphan*/  th_res; int /*<<< orphan*/  th_algo; } ;
struct timecounter {scalar_t__ tc_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  VDSO_TH_ALGO_X86_TSC ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static uint32_t
x86_tsc_vdso_timehands(struct vdso_timehands *vdso_th, struct timecounter *tc)
{

	vdso_th->th_algo = VDSO_TH_ALGO_X86_TSC;
	vdso_th->th_x86_shift = (int)(intptr_t)tc->tc_priv;
	vdso_th->th_x86_hpet_idx = 0xffffffff;
	bzero(vdso_th->th_res, sizeof(vdso_th->th_res));
	return (1);
}