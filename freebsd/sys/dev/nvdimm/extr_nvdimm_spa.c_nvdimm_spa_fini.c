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
struct SPA_mapping {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  nvdimm_spa_dev_fini (int /*<<< orphan*/ *) ; 

void
nvdimm_spa_fini(struct SPA_mapping *spa)
{

	nvdimm_spa_dev_fini(&spa->dev);
}