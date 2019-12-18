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
struct ppc4xx_msi {int /*<<< orphan*/  bitmap; } ;
struct TYPE_2__ {int /*<<< orphan*/  of_node; } ;
struct platform_device {TYPE_1__ dev; } ;

/* Variables and functions */
 int msi_bitmap_alloc (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msi_bitmap_free (int /*<<< orphan*/ *) ; 
 int msi_bitmap_reserve_dt_hwirqs (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msi_irqs ; 

__attribute__((used)) static int ppc4xx_msi_init_allocator(struct platform_device *dev,
		struct ppc4xx_msi *msi_data)
{
	int err;

	err = msi_bitmap_alloc(&msi_data->bitmap, msi_irqs,
			      dev->dev.of_node);
	if (err)
		return err;

	err = msi_bitmap_reserve_dt_hwirqs(&msi_data->bitmap);
	if (err < 0) {
		msi_bitmap_free(&msi_data->bitmap);
		return err;
	}

	return 0;
}