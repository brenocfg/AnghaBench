#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {unsigned int entropy; } ;
struct TYPE_5__ {int /*<<< orphan*/  lock; TYPE_1__ pool; } ;
typedef  TYPE_2__ isc_entropy_t ;

/* Variables and functions */
 int /*<<< orphan*/  LOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UNLOCK (int /*<<< orphan*/ *) ; 

unsigned int
isc_entropy_status(isc_entropy_t *ent) {
	unsigned int estimate;

	LOCK(&ent->lock);
	estimate = ent->pool.entropy;
	UNLOCK(&ent->lock);

	return estimate;
}