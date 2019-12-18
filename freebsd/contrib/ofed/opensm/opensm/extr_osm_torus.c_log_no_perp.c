#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct torus {TYPE_1__* osm; scalar_t__ debug; } ;
struct TYPE_2__ {int /*<<< orphan*/  log; } ;

/* Variables and functions */
 int /*<<< orphan*/  OSM_LOG (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,unsigned int,int,int,int,int,int,int) ; 
 int /*<<< orphan*/  OSM_LOG_INFO ; 

__attribute__((used)) static
void log_no_perp(struct torus *t, unsigned n,
		 int case_i, int case_j, int case_k,
		 int perp_i, int perp_j, int perp_k)
{
	if (t->debug)
		OSM_LOG(&t->osm->log, OSM_LOG_INFO, "Case 0x%03x "
			"@ %d %d %d: no perpendicular @ %d %d %d\n",
			n, case_i, case_j, case_k, perp_i, perp_j, perp_k);
}