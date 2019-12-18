#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct table_info {int dummy; } ;
struct numarray_cfg {int /*<<< orphan*/  used; int /*<<< orphan*/  size; } ;
struct numarray {int dummy; } ;
struct TYPE_3__ {int itemsize4; int /*<<< orphan*/  count4; int /*<<< orphan*/  size4; int /*<<< orphan*/  taclass4; } ;
typedef  TYPE_1__ ipfw_ta_tinfo ;

/* Variables and functions */
 int /*<<< orphan*/  IPFW_TACLASS_ARRAY ; 

__attribute__((used)) static void
ta_dump_numarray_tinfo(void *ta_state, struct table_info *ti, ipfw_ta_tinfo *tinfo)
{
	struct numarray_cfg *cfg;

	cfg = (struct numarray_cfg *)ta_state;

	tinfo->taclass4 = IPFW_TACLASS_ARRAY;
	tinfo->size4 = cfg->size;
	tinfo->count4 = cfg->used;
	tinfo->itemsize4 = sizeof(struct numarray);
}