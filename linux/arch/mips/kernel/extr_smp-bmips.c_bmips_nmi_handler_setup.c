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
 int /*<<< orphan*/  BMIPS_NMI_RESET_VEC ; 
 int /*<<< orphan*/  BMIPS_WARM_RESTART_VEC ; 
 int /*<<< orphan*/  bmips_reset_nmi_vec ; 
 int /*<<< orphan*/  bmips_reset_nmi_vec_end ; 
 int /*<<< orphan*/  bmips_smp_int_vec ; 
 int /*<<< orphan*/  bmips_smp_int_vec_end ; 
 int /*<<< orphan*/  bmips_wr_vec (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void bmips_nmi_handler_setup(void)
{
	bmips_wr_vec(BMIPS_NMI_RESET_VEC, bmips_reset_nmi_vec,
		bmips_reset_nmi_vec_end);
	bmips_wr_vec(BMIPS_WARM_RESTART_VEC, bmips_smp_int_vec,
		bmips_smp_int_vec_end);
}