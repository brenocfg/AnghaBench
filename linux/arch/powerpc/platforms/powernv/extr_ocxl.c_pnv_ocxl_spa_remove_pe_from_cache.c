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
struct spa_data {int /*<<< orphan*/  bdfn; int /*<<< orphan*/  phb_opal_id; } ;

/* Variables and functions */
 int opal_npu_spa_clear_cache (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int pnv_ocxl_spa_remove_pe_from_cache(void *platform_data, int pe_handle)
{
	struct spa_data *data = (struct spa_data *) platform_data;
	int rc;

	rc = opal_npu_spa_clear_cache(data->phb_opal_id, data->bdfn, pe_handle);
	return rc;
}