#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* uma_zone_t ;
typedef  scalar_t__ uma_maxaction_t ;
typedef  int /*<<< orphan*/  task_fn_t ;
struct TYPE_6__ {int /*<<< orphan*/  uz_maxaction; } ;

/* Variables and functions */
 int /*<<< orphan*/  TASK_INIT (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  ZONE_LOCK (TYPE_1__*) ; 
 int /*<<< orphan*/  ZONE_UNLOCK (TYPE_1__*) ; 

void
uma_zone_set_maxaction(uma_zone_t zone, uma_maxaction_t maxaction)
{

	ZONE_LOCK(zone);
	TASK_INIT(&zone->uz_maxaction, 0, (task_fn_t *)maxaction, zone);
	ZONE_UNLOCK(zone);
}