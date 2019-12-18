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
struct zynqmp_eemi_ops {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EPROBE_DEFER ; 
 struct zynqmp_eemi_ops const* ERR_PTR (int /*<<< orphan*/ ) ; 
 struct zynqmp_eemi_ops const* eemi_ops_tbl ; 

const struct zynqmp_eemi_ops *zynqmp_pm_get_eemi_ops(void)
{
	if (eemi_ops_tbl)
		return eemi_ops_tbl;
	else
		return ERR_PTR(-EPROBE_DEFER);

}