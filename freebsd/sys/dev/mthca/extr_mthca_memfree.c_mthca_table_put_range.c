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
struct mthca_icm_table {int obj_size; } ;
struct mthca_dev {int dummy; } ;

/* Variables and functions */
 int MTHCA_TABLE_CHUNK_SIZE ; 
 int /*<<< orphan*/  mthca_is_memfree (struct mthca_dev*) ; 
 int /*<<< orphan*/  mthca_table_put (struct mthca_dev*,struct mthca_icm_table*,int) ; 

void mthca_table_put_range(struct mthca_dev *dev, struct mthca_icm_table *table,
			   int start, int end)
{
	int i;

	if (!mthca_is_memfree(dev))
		return;

	for (i = start; i <= end; i += MTHCA_TABLE_CHUNK_SIZE / table->obj_size)
		mthca_table_put(dev, table, i);
}