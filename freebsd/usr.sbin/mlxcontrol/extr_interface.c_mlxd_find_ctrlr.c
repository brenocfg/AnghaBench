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
struct TYPE_2__ {int unit; int ctrlr; int sysdrive; } ;

/* Variables and functions */
 int /*<<< orphan*/  mlx_foreach (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_1__ mlxd_find_ctrlr_param ; 
 int /*<<< orphan*/  mlxd_find_ctrlr_search ; 

int
mlxd_find_ctrlr(int unit, int *ctrlr, int *sysdrive)
{
    mlxd_find_ctrlr_param.unit = unit;
    mlxd_find_ctrlr_param.ctrlr = -1;
    mlxd_find_ctrlr_param.sysdrive = -1;

    mlx_foreach(mlxd_find_ctrlr_search, NULL);
    if ((mlxd_find_ctrlr_param.ctrlr != -1) && (mlxd_find_ctrlr_param.sysdrive != -1)) {
	*ctrlr = mlxd_find_ctrlr_param.ctrlr;
	*sysdrive = mlxd_find_ctrlr_param.sysdrive;
	return(0);
    }
    return(1);
}