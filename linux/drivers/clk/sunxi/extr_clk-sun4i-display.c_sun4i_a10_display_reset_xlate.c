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
struct reset_controller_dev {int dummy; } ;
struct of_phandle_args {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static int sun4i_a10_display_reset_xlate(struct reset_controller_dev *rcdev,
					 const struct of_phandle_args *spec)
{
	/* We only have a single reset signal */
	return 0;
}