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
struct TYPE_3__ {scalar_t__ used; int /*<<< orphan*/  lock; scalar_t__ soft; scalar_t__ max; } ;
typedef  TYPE_1__ isc_quota_t ;

/* Variables and functions */
 int /*<<< orphan*/  DESTROYLOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INSIST (int) ; 

void
isc_quota_destroy(isc_quota_t *quota) {
	INSIST(quota->used == 0);
	quota->max = 0;
	quota->used = 0;
	quota->soft = 0;
	DESTROYLOCK(&quota->lock);
}