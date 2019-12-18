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
struct radix_cfg {int /*<<< orphan*/  count6; int /*<<< orphan*/  count4; } ;
struct radix_addr_xentry {int dummy; } ;
struct radix_addr_entry {int dummy; } ;
struct TYPE_3__ {int flags; int itemsize4; int itemsize6; int /*<<< orphan*/  count6; void* taclass6; int /*<<< orphan*/  count4; void* taclass4; } ;
typedef  TYPE_1__ ipfw_ta_tinfo ;

/* Variables and functions */
 void* IPFW_TACLASS_RADIX ; 
 int IPFW_TATFLAGS_AFDATA ; 
 int IPFW_TATFLAGS_AFITEM ; 

__attribute__((used)) static void
ta_dump_radix_tinfo(void *ta_state, struct table_info *ti, ipfw_ta_tinfo *tinfo)
{
	struct radix_cfg *cfg;

	cfg = (struct radix_cfg *)ta_state;

	tinfo->flags = IPFW_TATFLAGS_AFDATA | IPFW_TATFLAGS_AFITEM;
	tinfo->taclass4 = IPFW_TACLASS_RADIX;
	tinfo->count4 = cfg->count4;
	tinfo->itemsize4 = sizeof(struct radix_addr_entry);
	tinfo->taclass6 = IPFW_TACLASS_RADIX;
	tinfo->count6 = cfg->count6;
	tinfo->itemsize6 = sizeof(struct radix_addr_xentry);
}