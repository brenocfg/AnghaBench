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
typedef  int /*<<< orphan*/  uma_zone_t ;

/* Variables and functions */
 int /*<<< orphan*/  SKIP_NONE ; 
 int /*<<< orphan*/  sx_slock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_sunlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uma_reclaim_lock ; 
 int /*<<< orphan*/  zone_free_item (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zones ; 

void
uma_zdestroy(uma_zone_t zone)
{

	sx_slock(&uma_reclaim_lock);
	zone_free_item(zones, zone, NULL, SKIP_NONE);
	sx_sunlock(&uma_reclaim_lock);
}