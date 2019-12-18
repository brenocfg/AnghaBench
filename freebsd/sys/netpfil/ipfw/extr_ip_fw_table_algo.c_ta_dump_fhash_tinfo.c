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
struct fhashentry6 {int dummy; } ;
struct fhashentry4 {int dummy; } ;
struct fhash_cfg {int /*<<< orphan*/  items; int /*<<< orphan*/  size; } ;
struct TYPE_3__ {int itemsize4; int itemsize6; int /*<<< orphan*/  count4; int /*<<< orphan*/  size4; int /*<<< orphan*/  taclass4; int /*<<< orphan*/  flags; } ;
typedef  TYPE_1__ ipfw_ta_tinfo ;

/* Variables and functions */
 int /*<<< orphan*/  IPFW_TACLASS_HASH ; 
 int /*<<< orphan*/  IPFW_TATFLAGS_AFITEM ; 

__attribute__((used)) static void
ta_dump_fhash_tinfo(void *ta_state, struct table_info *ti, ipfw_ta_tinfo *tinfo)
{
	struct fhash_cfg *cfg;

	cfg = (struct fhash_cfg *)ta_state;

	tinfo->flags = IPFW_TATFLAGS_AFITEM;
	tinfo->taclass4 = IPFW_TACLASS_HASH;
	tinfo->size4 = cfg->size;
	tinfo->count4 = cfg->items;
	tinfo->itemsize4 = sizeof(struct fhashentry4);
	tinfo->itemsize6 = sizeof(struct fhashentry6);
}