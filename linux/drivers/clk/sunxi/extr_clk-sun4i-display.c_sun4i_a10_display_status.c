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
struct reset_data {scalar_t__ offset; int /*<<< orphan*/  reg; } ;
struct reset_controller_dev {int dummy; } ;

/* Variables and functions */
 int BIT (scalar_t__) ; 
 struct reset_data* rcdev_to_reset_data (struct reset_controller_dev*) ; 
 int readl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sun4i_a10_display_status(struct reset_controller_dev *rcdev,
				    unsigned long id)
{
	struct reset_data *data = rcdev_to_reset_data(rcdev);

	return !(readl(data->reg) & BIT(data->offset + id));
}