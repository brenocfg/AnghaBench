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
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  spa_t ;
struct TYPE_3__ {scalar_t__ dds_dsize; scalar_t__ dds_ref_dsize; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ ddt_stat_t ;

/* Variables and functions */
 int /*<<< orphan*/  ddt_get_dedup_stats (int /*<<< orphan*/ *,TYPE_1__*) ; 

uint64_t
ddt_get_dedup_dspace(spa_t *spa)
{
	ddt_stat_t dds_total = { 0 };

	ddt_get_dedup_stats(spa, &dds_total);
	return (dds_total.dds_ref_dsize - dds_total.dds_dsize);
}