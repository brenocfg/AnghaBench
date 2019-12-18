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
struct rtentry {int dummy; } ;
struct TYPE_3__ {int itemsize4; int itemsize6; scalar_t__ count6; void* taclass6; scalar_t__ count4; void* taclass4; int /*<<< orphan*/  flags; } ;
typedef  TYPE_1__ ipfw_ta_tinfo ;

/* Variables and functions */
 void* IPFW_TACLASS_RADIX ; 
 int /*<<< orphan*/  IPFW_TATFLAGS_AFDATA ; 

__attribute__((used)) static void
ta_dump_kfib_tinfo(void *ta_state, struct table_info *ti, ipfw_ta_tinfo *tinfo)
{

	tinfo->flags = IPFW_TATFLAGS_AFDATA;
	tinfo->taclass4 = IPFW_TACLASS_RADIX;
	tinfo->count4 = 0;
	tinfo->itemsize4 = sizeof(struct rtentry);
	tinfo->taclass6 = IPFW_TACLASS_RADIX;
	tinfo->count6 = 0;
	tinfo->itemsize6 = sizeof(struct rtentry);
}