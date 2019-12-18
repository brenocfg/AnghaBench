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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  u_long ;
struct cpuref {int dummy; } ;
typedef  int /*<<< orphan*/  platform_t ;

/* Variables and functions */
 int /*<<< orphan*/  PS3_LPAR_ID_PME ; 
 int /*<<< orphan*/  lv1_get_repository_node_value (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int lv1_repository_string (char*) ; 

__attribute__((used)) static u_long
ps3_timebase_freq(platform_t plat, struct cpuref *cpuref)
{
	uint64_t ticks, node_id, junk;

	lv1_get_repository_node_value(PS3_LPAR_ID_PME, 
	    lv1_repository_string("be") >> 32, 0, 0, 0, &node_id, &junk);
	lv1_get_repository_node_value(PS3_LPAR_ID_PME,
	    lv1_repository_string("be") >> 32, node_id,
	    lv1_repository_string("clock"), 0, &ticks, &junk);

	return (ticks);
}