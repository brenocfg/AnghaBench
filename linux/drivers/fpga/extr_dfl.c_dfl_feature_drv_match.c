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
struct dfl_feature_id {scalar_t__ id; } ;
struct dfl_feature_driver {struct dfl_feature_id* id_table; } ;
struct dfl_feature {scalar_t__ id; } ;

/* Variables and functions */

__attribute__((used)) static bool dfl_feature_drv_match(struct dfl_feature *feature,
				  struct dfl_feature_driver *driver)
{
	const struct dfl_feature_id *ids = driver->id_table;

	if (ids) {
		while (ids->id) {
			if (ids->id == feature->id)
				return true;
			ids++;
		}
	}
	return false;
}