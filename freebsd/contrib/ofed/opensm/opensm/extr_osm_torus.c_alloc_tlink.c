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
struct torus {scalar_t__ link_cnt; scalar_t__ link_pool_sz; struct link* link_pool; TYPE_1__* osm; } ;
struct link {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  log; } ;

/* Variables and functions */
 int /*<<< orphan*/  OSM_LOG (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  OSM_LOG_ERROR ; 

__attribute__((used)) static
struct link *alloc_tlink(struct torus *t)
{
	if (t->link_cnt >= t->link_pool_sz) {
		OSM_LOG(&t->osm->log, OSM_LOG_ERROR,
			"ERR 4E16: unexpectedly out of pre-allocated link "
			"structures!\n");
		return NULL;
	}
	return &t->link_pool[t->link_cnt++];
}