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
struct dev_pagemap {int dummy; } ;
struct dev_dax {int dummy; } ;
struct dax_region {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEV_DAX_BUS ; 
 struct dev_dax* __devm_create_dev_dax (struct dax_region*,int,struct dev_pagemap*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline struct dev_dax *devm_create_dev_dax(struct dax_region *dax_region,
		int id, struct dev_pagemap *pgmap)
{
	return __devm_create_dev_dax(dax_region, id, pgmap, DEV_DAX_BUS);
}