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
struct chashentry {int dummy; } ;
struct chash_cfg {int /*<<< orphan*/  items6; int /*<<< orphan*/  size6; int /*<<< orphan*/  items4; int /*<<< orphan*/  size4; } ;
struct TYPE_3__ {int flags; int itemsize4; int itemsize6; int /*<<< orphan*/  count6; int /*<<< orphan*/  size6; void* taclass6; int /*<<< orphan*/  count4; int /*<<< orphan*/  size4; void* taclass4; } ;
typedef  TYPE_1__ ipfw_ta_tinfo ;

/* Variables and functions */
 void* IPFW_TACLASS_HASH ; 
 int IPFW_TATFLAGS_AFDATA ; 
 int IPFW_TATFLAGS_AFITEM ; 

__attribute__((used)) static void
ta_dump_chash_tinfo(void *ta_state, struct table_info *ti, ipfw_ta_tinfo *tinfo)
{
	struct chash_cfg *cfg;

	cfg = (struct chash_cfg *)ta_state;

	tinfo->flags = IPFW_TATFLAGS_AFDATA | IPFW_TATFLAGS_AFITEM;
	tinfo->taclass4 = IPFW_TACLASS_HASH;
	tinfo->size4 = cfg->size4;
	tinfo->count4 = cfg->items4;
	tinfo->itemsize4 = sizeof(struct chashentry);
	tinfo->taclass6 = IPFW_TACLASS_HASH;
	tinfo->size6 = cfg->size6;
	tinfo->count6 = cfg->items6;
	tinfo->itemsize6 = sizeof(struct chashentry);
}