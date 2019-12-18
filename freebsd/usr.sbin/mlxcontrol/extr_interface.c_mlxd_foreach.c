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
struct mlxd_foreach_action {void (* func ) (int,void*) ;void* arg; } ;

/* Variables and functions */
 int /*<<< orphan*/  mlx_foreach (int /*<<< orphan*/ ,struct mlxd_foreach_action*) ; 
 int /*<<< orphan*/  mlxd_foreach_ctrlr ; 

void
mlxd_foreach(void (*func)(int unit, void *arg), void *arg)
{
    struct mlxd_foreach_action ma;
    
    ma.func = func;
    ma.arg = arg;
    mlx_foreach(mlxd_foreach_ctrlr, &ma);
}