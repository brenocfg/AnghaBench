#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* uma_zone_t ;
struct TYPE_5__ {int /*<<< orphan*/ * ta_func; } ;
struct TYPE_4__ {TYPE_3__ uz_maxaction; } ;

/* Variables and functions */
 int /*<<< orphan*/  taskqueue_enqueue (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  taskqueue_thread ; 

__attribute__((used)) static inline void
zone_maxaction(uma_zone_t zone)
{

	if (zone->uz_maxaction.ta_func != NULL)
		taskqueue_enqueue(taskqueue_thread, &zone->uz_maxaction);
}