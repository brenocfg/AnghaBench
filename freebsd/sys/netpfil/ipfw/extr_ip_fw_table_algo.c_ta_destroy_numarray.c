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
struct table_info {int dummy; } ;
struct numarray_cfg {struct numarray_cfg* main_ptr; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_IPFW ; 
 int /*<<< orphan*/  free (struct numarray_cfg*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ta_destroy_numarray(void *ta_state, struct table_info *ti)
{
	struct numarray_cfg *cfg;

	cfg = (struct numarray_cfg *)ta_state;

	if (cfg->main_ptr != NULL)
		free(cfg->main_ptr, M_IPFW);

	free(cfg, M_IPFW);
}