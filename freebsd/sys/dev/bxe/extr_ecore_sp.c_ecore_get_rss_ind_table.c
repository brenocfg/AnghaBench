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
typedef  int /*<<< orphan*/  uint8_t ;
struct ecore_rss_config_obj {int /*<<< orphan*/  ind_table; } ;

/* Variables and functions */
 int /*<<< orphan*/  ECORE_MEMCPY (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

void ecore_get_rss_ind_table(struct ecore_rss_config_obj *rss_obj,
			     uint8_t *ind_table)
{
	ECORE_MEMCPY(ind_table, rss_obj->ind_table, sizeof(rss_obj->ind_table));
}