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
 int /*<<< orphan*/  mlx4_driver_init ; 
 int /*<<< orphan*/  verbs_register_driver (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static __attribute__((constructor)) void mlx4_register_driver(void)
{
	verbs_register_driver("mlx4", mlx4_driver_init);
}