#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_5__ {int /*<<< orphan*/  lookup; } ;
typedef  TYPE_1__ ocs_sport_t ;
typedef  int /*<<< orphan*/  ocs_node_t ;

/* Variables and functions */
 int /*<<< orphan*/  ocs_assert (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocs_sport_lock (TYPE_1__*) ; 
 int /*<<< orphan*/  ocs_sport_unlock (TYPE_1__*) ; 
 int /*<<< orphan*/ * spv_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

ocs_node_t *
ocs_node_find(ocs_sport_t *sport, uint32_t port_id)
{
	ocs_node_t *node;

	ocs_assert(sport->lookup, NULL);
	ocs_sport_lock(sport);
		node = spv_get(sport->lookup, port_id);
	ocs_sport_unlock(sport);
	return node;
}