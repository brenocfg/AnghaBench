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
typedef  scalar_t__ u64 ;
struct mthca_uar {int index; } ;
struct TYPE_2__ {int uarc_size; scalar_t__ uarc_base; } ;
struct mthca_dev {TYPE_1__ uar_table; } ;

/* Variables and functions */
 int MTHCA_ICM_PAGE_SIZE ; 

__attribute__((used)) static u64 mthca_uarc_virt(struct mthca_dev *dev, struct mthca_uar *uar, int page)
{
	return dev->uar_table.uarc_base +
		uar->index * dev->uar_table.uarc_size +
		page * MTHCA_ICM_PAGE_SIZE;
}