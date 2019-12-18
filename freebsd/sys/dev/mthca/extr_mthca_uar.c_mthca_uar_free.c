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
struct mthca_uar {int /*<<< orphan*/  index; } ;
struct TYPE_2__ {int /*<<< orphan*/  alloc; } ;
struct mthca_dev {TYPE_1__ uar_table; } ;

/* Variables and functions */
 int /*<<< orphan*/  mthca_free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void mthca_uar_free(struct mthca_dev *dev, struct mthca_uar *uar)
{
	mthca_free(&dev->uar_table.alloc, uar->index);
}