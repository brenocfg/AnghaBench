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
struct _citrus_mapper {int /*<<< orphan*/  cm_refcount; } ;

/* Variables and functions */
 int /*<<< orphan*/  REFCOUNT_PERSISTENT ; 
 int /*<<< orphan*/  UNLOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WLOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cm_lock ; 

void
_citrus_mapper_set_persistent(struct _citrus_mapper * __restrict cm)
{

	WLOCK(&cm_lock);
	cm->cm_refcount = REFCOUNT_PERSISTENT;
	UNLOCK(&cm_lock);
}